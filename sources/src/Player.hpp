#pragma once

#include <glimac/FreeflyCamera.hpp>

namespace glimac {

	enum State {Jumping, Falling, Walking, unMoving}; //  0 1 2

	class Player {
		void build(glm::vec3 position);

		public:
      Player(glm::vec3 position) {
          build(position);
      }
      State state = unMoving;
			FreeflyCamera camera;

			void moveFront(float t);
			void moveLeft(float t);
  		void rotateLeft(float degrees);
			void rotateUp(float degrees);
			void jump(float t);
			void display();
			void updateAlt(float t);

		private:
			glm::vec3 position;
			float threshold;
			float alt;
	};
}