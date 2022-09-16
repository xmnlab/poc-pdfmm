test_suite = [
  ['poc-pdfmm', files(PROJECT_PATH + '/tests/test-poc-pdfmm.cpp')],
]

foreach test_item : test_suite
    test_name = test_item[0]
    test_src_files = test_item[1] + files(PROJECT_PATH + '/tests/main.cpp')

    executable_name_suffix = test_name + '_tests'
    test_executable = executable(
      'poc-pdfmm' + executable_name_suffix,
      test_src_files,
      include_directories : inc,
      dependencies : deps,
      link_with: [lib] + libs_3rd_party)

    test(
      executable_name_suffix,
      test_executable,
      workdir : meson.source_root())
endforeach
