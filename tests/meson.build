gtest_dep = dependency('gtest', required: true)
gtest_main_dep = dependency('gtest_main', required: true)

test_executable = executable('liltests', 'test_main.cpp',
  include_directories: include_directories('../lib'),
  dependencies: [gtest_dep, gtest_main_dep],
  link_with: lib)

test('basic', test_executable)
