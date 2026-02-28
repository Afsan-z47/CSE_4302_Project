ncurses_dep = dependency('ncurses')

# List all source files
sources = files(
  'main.cpp',
  'user.cpp',
  'course.cpp',
  'assessment.cpp',
  'schoolsystem.cpp',
  'grade.cpp',
  'AttendanceRecord.h',
  'RecordCard.h',
  'file_ops.h',
  # 'other.cpp',  # Add additional files here. Make sure previous line ends with a comma
)

core_lib = static_library('core', sources)

# Build the executable
executable('project.o', 'main.cpp', link_with: core_lib)

# Clang-Tidy integration
clang_tidy = find_program('clang-tidy', required: true)
config_file = meson.project_source_root() + '/.clang-tidy'

# Run clang-tidy on all source files (output to terminal)
run_target(
  'tidy',
  command : [
    clang_tidy,
    sources,
    '--config-file=' + config_file,
    '--',
    '-std=c++20',
    '-I', meson.current_source_dir()
  ]
)

# Additional target to run clang-tidy with fixes
run_target(
  'tidy-fix',
  command : [
    clang_tidy,
    sources,
    '--config-file=' + config_file,
    '--fix',
    '--',
    '-std=c++20',
    '-I', meson.current_source_dir()
  ]
)
