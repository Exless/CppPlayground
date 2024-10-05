#include <iostream>
#include <memory>

#include <fmt/format.h>
#include "Vertex.h"
#include "easylogging++.h"
#include <nlohmann/json.hpp>
#include <fruit/fruit.h>

using fmt::format;
using nlohmann::json;


INITIALIZE_EASYLOGGINGPP

void setupLogging()
{
  el::Configurations defaultConf;
  defaultConf.setToDefault();

  // Set the format for all levels
  defaultConf.set(el::Level::Global, el::ConfigurationType::Format,
                  "%datetime | %level | %fbase:%line - %func | %msg"
                  );
  el::Loggers::reconfigureLogger("default", defaultConf);
}


/**
 * This function adds two integers
 * @param x the x parameter
 * @param y the y parameter
 * @return the sum of the two
 */
int adds(const int x, const int y)
{
  return x + y;
}

int main()
{
  setupLogging();

  auto i = std::make_unique<int>(32);
  auto yy = adds(2, 3);
  auto vertex = std::make_unique<Vertex>(2, 3, 1);

  LOG(INFO) << "Hello, World!";
  LOG(INFO) << format("The value is {}", *i);
  LOG(INFO) << format("The memory address is {}", static_cast<void*>(i.get()));
  LOG(INFO) << format("The vertex is x={}, y={}, z={}", vertex->x, vertex->y, vertex->z);

  json jsonDto = {
    {"this is one value", 3},
    {"this is a vertex", "vertex value"}
  };

  auto jsonStr = jsonDto.dump();

  LOG(INFO) << format("This is the json {}", jsonStr);

  return 0;
}
