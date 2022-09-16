project('pocpdfmm', 'cpp', 'c',
  license : 'MIT',
  version : '1.0.0',  # semantic-release
  default_options : [
    'warning_level=3',
    'cpp_std=c++17',
  ]
)

PROJECT_PATH = meson.source_root()

cxx = meson.get_compiler('cpp')

deps = [
  dependency('CLI11'),
  dependency('glog'),
]

libs_3rd_party = [
  static_library('libpdfmm.so'),
]

CONDA_PREFIX = run_command('sh', '-c', 'echo $CONDA_PREFIX').stdout().strip()

inc = include_directories(
  './poc-pdfmm/include',
  CONDA_PREFIX + '/include/pdfmm'
)

POC_PDFMM_SRC_PATH = PROJECT_PATH + '/poc-pdfmm/src'

project_src_files = files(
  POC_PDFMM_SRC_PATH + '/example.cpp',
)

gtest_dep = dependency('gtest', main : true, required: get_option('dev'))
gmock_dep = dependency('gmock', required: get_option('dev'))

clangtidy = find_program('clang-tidy', required: get_option('dev'))
if clangtidy.found()
  run_target(
    'clang-tidy',
    command: [
      PROJECT_PATH + '/scripts/run-clang-tidy.sh',
    ])
endif

lib = library(
  'poc-pdfmm-lib',
  project_src_files,
  include_directories : inc,
  install : true,
  dependencies : deps,
  link_with : libs_3rd_party)

exe = executable(
  'pocpdfmm',
  files(POC_PDFMM_SRC_PATH + '/main.cpp'),
  dependencies : deps,
  include_directories : inc,
  install : true,
  link_with : [lib] + libs_3rd_party)

if get_option('dev').enabled()
  deps += [gtest_dep, gmock_dep]
  subdir('tests')
endif
