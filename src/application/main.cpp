#include "hadron/application/application.h"
#include "hadron/application/main.h"

int32_t main(const int32_t argc, const char** argv) {
  Application* app = create(argc, argv);
  app->reset();
  app->run();
  delete app;
  return 0;
}
