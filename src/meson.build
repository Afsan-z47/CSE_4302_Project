# List all source files
sources = files(
  'main.cpp'
  # 'other.cpp',  # Add additional files here. Make sure previous line ends with a comma
)

# Build the executable
executable('project.o', sources)

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
