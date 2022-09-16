#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>

#include <glog/logging.h>

#include "poc-pdfmm.h"

const std::string POCPDFMM_VERSION = "1.0.0";  // semantic-release

auto show_version(int count) -> void {
  std::cout << "PoC PDFMM version: " << POCPDFMM_VERSION
            << std::endl;
  exit(0);
}

auto main(int argc, const char* argv[]) -> int {
  google::InitGoogleLogging(argv[0]);

  CLI::App app{"PoCPDFMM"};

  app.add_flag("--version", show_version, "Show PoC PDFmm version.");

  CLI11_PARSE(app, argc, argv);

  return 0;
}
