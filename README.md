YOU CAN FIND 
Model, View, Projection matrices algorithms from scratch Added(My own Glm library)
You can find it in linear_algebros.cpp
I wrote it from wikipedia


NOTE if you want to use "linear_algebros.cpp" algorithm which is my own code
   dont forget the add "src/linear_algebros.cpp" to CmakeLists
   
use vec3 like quad_position = {-0.2f, 0.4f, 0.0f}; dont use glm::vec3 

use mat4 like view = create_look_at(camera_pos, camera_target); dont use glm::mat4 
