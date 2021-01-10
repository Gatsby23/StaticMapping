// MIT License

// Copyright (c) 2019 Edward Liu

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef PRE_PROCESSORS_FILTER_FACTORY_H_
#define PRE_PROCESSORS_FILTER_FACTORY_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "pre_processors/filter_interface.h"
#include "pugixml/pugixml.hpp"

namespace static_map {
namespace pre_processers {
namespace filter {

class Factory : public Interface {
 public:
  Factory() : Interface() { RegisterSupportedFilters(); }
  ~Factory() = default;

  Factory(const Factory&) = delete;
  Factory& operator=(const Factory&) = delete;

  std::shared_ptr<Interface> CreateNewInstance() override {
    return std::make_shared<Factory>();
  }

  /* example
  <filters>
    <filter name="RandomSampler">
      <param type="1" name="sampling_rate"> 0.8 </param>
    </filter>
    ...
  </filters>
  */
  void InitFromXmlText(const char* text);

  void InitFromXmlNode(const pugi::xml_node& filters_node);

  void Filter(const data::InnerCloudType::Ptr& cloud) override;

 protected:
  void RegisterSupportedFilters();

 private:
  std::vector<std::shared_ptr<Interface>> filters_;
  std::map<std::string, std::shared_ptr<Interface>> supported_filters_;
};

}  // namespace filter
}  // namespace pre_processers
}  // namespace static_map

#endif  // PRE_PROCESSORS_FILTER_FACTORY_H_
