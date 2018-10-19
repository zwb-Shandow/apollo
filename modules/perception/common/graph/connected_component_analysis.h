/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#pragma once

#include <queue>
#include <vector>

#include "cyber/common/log.h"

namespace apollo {
namespace perception {
namespace common {

/*
* @brief: bfs based connected component analysis
* @params[IN] graph: input graph for connected component analysis
* @params[OUT] components: connected components of input graph
* @return nothing
* */
void ConnectedComponentAnalysis(const std::vector<std::vector<int>>& graph,
                                std::vector<std::vector<int>>* components) {
  CHECK_NOTNULL(components);
  int num_item = graph.size();
  std::vector<int> visited;
  visited.resize(num_item, 0);
  std::queue<int> que;
  std::vector<int> component;
  component.reserve(num_item);
  components->clear();

  for (int index = 0; index < num_item; ++index) {
    if (visited[index]) {
      continue;
    }
    component.push_back(index);
    que.push(index);
    visited[index] = 1;
    while (!que.empty()) {
      int current_id = que.front();
      que.pop();
      for (size_t sub_index = 0; sub_index < graph[current_id].size();
           ++sub_index) {
        int neighbor_id = graph[current_id][sub_index];
        if (visited[neighbor_id] == 0) {
          component.push_back(neighbor_id);
          que.push(neighbor_id);
          visited[neighbor_id] = 1;
        }
      }
    }
    components->push_back(component);
    component.clear();
  }
}

}  // namespace common
}  // namespace perception
}  // namespace apollo
