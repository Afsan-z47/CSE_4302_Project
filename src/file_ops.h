#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <iosfwd>

template<typename T>
class File_ops {
public:
	virtual void save(std::ostream &f_out) const = 0;
	virtual T load(std::istream &f_in) = 0;

	File_ops(const File_ops &) = delete;
	File_ops(File_ops &&) = delete;
	File_ops &operator=(const File_ops &) = delete;
	File_ops &operator=(File_ops &&) = delete;

protected:
	virtual ~File_ops() = default;
};

#endif
