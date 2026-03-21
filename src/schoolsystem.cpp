/*
 * schoolsystem.cpp — Multi-instance School Management System
 * ===========================================================
 *
 * Multi-terminal design
 * ─────────────────────
 *   Multiple terminals may run SchoolSystem simultaneously against the
 *   same set of data files.  A shared "instance counter" file — protected
 *   by POSIX flock(2) — tracks how many live processes share the data.
 *
 *   • Every instance LOADS all data into its own in-memory vectors on
 *     construction.
 *   • Every instance operates on its private in-memory copy while alive.
 *   • The LAST instance to shut down (counter → 0) writes all vectors
 *     back to disk, providing a consistent final state.
 *
 * Known limitations / future work
 * ────────────────────────────────
 *   [ ] Concurrent mutations from two live instances are NOT merged —
 *       last-writer-wins.  A shared in-memory server (or merge log)
 *       would be required for true concurrent edits.
 *   [ ] Teacher class is stubbed; fill in once teacher.h is complete.
 *   [ ] Grade/report card is stubbed pending Assessment ↔ Course linkage.
 */

#include "assessment.h" // defines Assessment
#include "course.cpp"     // defines Course (includes grade.cpp internally)
#include "grade.h"      // defines Grade  (includes assessment.cpp internally)

#include "AttendanceRecord.h"
#include "file_ops.h"
#include "user.h"

#include <fcntl.h>    // open(2)
#include <sys/file.h> // flock(2)
#include <unistd.h>   // close, ftruncate, lseek, read, write

#include <cstdint>
#include <cstdlib> // atoi
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

enum Privilege_type : uint8_t {
	GUEST   = 0,
	STUDENT = 1,
	TEACHER = 2,
	ADMIN   = 3,
};

// FIXME: Will think about these stuff later
//	For now, its something to move around

// ═══════════════════════════════════════════════════════════════════
//  InstanceGuard
//  ─────────────
//  RAII wrapper that keeps a reference-counted integer in a plain-text
//  file, protected by POSIX flock(2).
//
//    Construction : increment counter  → signals "I am alive"
//    release()    : decrement counter  → returns true when counter == 0
//                   (caller should then flush data to disk)
// ═══════════════════════════════════════════════════════════════════

class InstanceGuard {
	int fd_{-1};

	// Exclusive lock / unlock on the file descriptor.
	void lock() { ::flock(fd_, LOCK_EX); }
	void unlock() { ::flock(fd_, LOCK_UN); }

	int readCount() {
		::lseek(fd_, 0, SEEK_SET);
		char buf[32]{};
		::read(fd_, buf, sizeof(buf) - 1);
		int n = std::atoi(buf);
		return n < 0 ? 0 : n;
	}

	void writeCount(int n) {
		if (n < 0)
			n = 0;
		::lseek(fd_, 0, SEEK_SET);
		::ftruncate(fd_, 0);
		const std::string s = std::to_string(n);
		::write(fd_, s.c_str(), s.size());
	}

public:
	explicit InstanceGuard(const std::string &lockFilePath) {
		fd_ = ::open(lockFilePath.c_str(), O_RDWR | O_CREAT, 0666);
		if (fd_ < 0)
			throw std::runtime_error("InstanceGuard: cannot open lock file: " + lockFilePath);
		lock();
		writeCount(readCount() + 1);
		unlock();
	}

	// Decrements the counter.  Returns true when this was the last instance.
	bool release() noexcept {
		if (fd_ < 0)
			return false;
		lock();
		const int remaining = readCount() - 1;
		writeCount(remaining);
		unlock();
		::close(fd_);
		fd_ = -1;
		return remaining <= 0;
	}

	~InstanceGuard() {
		if (fd_ >= 0)
			::close(fd_);
	}

	InstanceGuard(const InstanceGuard &)            = delete;
	InstanceGuard &operator=(const InstanceGuard &) = delete;
	InstanceGuard(InstanceGuard &&)                 = delete;
	InstanceGuard &operator=(InstanceGuard &&)      = delete;
};

class SchoolSystem {
public:
	// ── Path bundle ──────────────────────────────────────────────────────
	struct DataPaths {
		std::string students;   // one serialised Student per line
		std::string admins;     // one serialised Admin per line
		std::string courses;    // one serialised Course per line
		std::string attendance; // one serialised AttendanceRecord per line
		std::string lockFile;   // shared instance-counter file
	};

private:
	// ── Coordination & session ───────────────────────────────────────────
	DataPaths      paths_;
	InstanceGuard  guard_;
	Privilege_type privilege_{GUEST};
	std::string    currentUserID_;

	// ── In-memory stores ─────────────────────────────────────────────────
	std::vector<Student>          students_;
	std::vector<Admin>            admins_;
	std::vector<Course>           courses_;
	std::vector<AttendanceRecord> attendance_;

	// ─────────────────────────────────────────────────────────────────────
	//  I/O helpers (load / save each entity type)
	// ─────────────────────────────────────────────────────────────────────

	void loadStudents() {
		std::ifstream f(paths_.students);
		if (!f)
			return;
		std::string line;
		while (std::getline(f, line))
			if (!line.empty())
				students_.push_back(Student::fromLine(line));
		// Keep the global student counter in sync so generateSID() is correct.
		students = static_cast<int>(students_.size());
	}

	void saveStudents() const {
		std::ofstream f(paths_.students, std::ios::trunc);
		for (const auto &s : students_)
			f << s.serialize() << '\n';
	}
};
