#include "glimac/Map.hpp"
#include <cmath>

namespace glimac {


	void Map::buildLevel(std::string path, TextureManager& textureManager, unsigned int levelNumber) {
		cv::Mat level = cv::imread(path, 1);

		for(int x=0; x < level.rows; ++x) {
		 	for(int y=0; y < level.cols; ++y) {
		 		int posY = y - level.cols/2;
		 		int posX = x - level.rows/2;

		 		
				CubeAtom cubeAtom;
				cubeAtom.position = glm::vec3( posY, levelNumber, posX);
				cubeAtom.moveThrough = false;

				cv::Vec3b colorRed(254, 0, 0),
					colorGreen(0, 254, 0),
					colorBlue(0, 0, 254);

				cv::Vec3b color = level.at<cv::Vec3b>(x, y);

				switch(levelNumber) {

				case 0:
					if ((int)level.at<cv::Vec3b>(x,y)[0] > (int)level.at<cv::Vec3b>(x,y)[2] &&
						(int)level.at<cv::Vec3b>(x,y)[0] > (int)level.at<cv::Vec3b>(x,y)[1]) {
						const Texture& texture = textureManager.get("assets/textures/water.png");
						cubeAtom.tex_id = texture.getId();

						undestructibleCube.push_back(cubeAtom);

					}
					if ((int)level.at<cv::Vec3b>(x,y)[1] > (int)level.at<cv::Vec3b>(x,y)[2] &&
						(int)level.at<cv::Vec3b>(x,y)[1] > (int)level.at<cv::Vec3b>(x,y)[0]) {
						Tree tree(glm::vec3( posY, levelNumber  , posX), textureManager);
						std::vector<CubeAtom> cubes = tree.getAllTreeCubes();
						for(auto& cubeAtom : cubes){
							destructibleCube.push_back(cubeAtom);
						}

						
					} 
					if((int)level.at<cv::Vec3b>(x,y)[2] > (int)level.at<cv::Vec3b>(x,y)[0] &&
						(int)level.at<cv::Vec3b>(x,y)[2] > (int)level.at<cv::Vec3b>(x,y)[1]) { 
						const Texture& texture = textureManager.get("assets/textures/sand.jpg");
						cubeAtom.tex_id = texture.getId();
						cubeAtom.moveThrough = true;

						undestructibleCube.push_back(cubeAtom);
					}
					break;

				case 1:
					if ((int)level.at<cv::Vec3b>(x,y)[0] < (int)level.at<cv::Vec3b>(x,y)[2]) {
						const Texture& texture = textureManager.get("assets/textures/sand.jpg");
						cubeAtom.tex_id = texture.getId();

						destructibleCube.push_back(cubeAtom);
					}
					break;

				case 2:
					if ((int)level.at<cv::Vec3b>(x,y)[0] < (int)level.at<cv::Vec3b>(x,y)[2]) {
						const Texture& texture = textureManager.get("assets/textures/herbe.jpg");
						cubeAtom.tex_id = texture.getId();

						destructibleCube.push_back(cubeAtom);
					}
					break;

				default:
					if((int)level.at<cv::Vec3b>(x,y)[2] > (int)level.at<cv::Vec3b>(x,y)[0] &&
						(int)level.at<cv::Vec3b>(x,y)[2] > (int)level.at<cv::Vec3b>(x,y)[1]) {
						const Texture& texture = textureManager.get("assets/textures/rock.png");
						cubeAtom.tex_id = texture.getId();

						destructibleCube.push_back(cubeAtom);
					}
					if ((int)level.at<cv::Vec3b>(x,y)[1] > (int)level.at<cv::Vec3b>(x,y)[2] &&
						(int)level.at<cv::Vec3b>(x,y)[1] > (int)level.at<cv::Vec3b>(x,y)[0]) {
						Tree tree(glm::vec3( posY, levelNumber  , posX), textureManager);
						std::vector<CubeAtom> cubes = tree.getAllTreeCubes();
						for(auto& cubeAtom : cubes){
							destructibleCube.push_back(cubeAtom);
						}

						
					} 
					break;
				}
			}
		}
	}

	void Map::buildMap(TextureManager& textureManager) {
		destructibleCube.clear();
		undestructibleCube.clear();

		buildLevel("assets/Map/sea_ground.jpg", textureManager, 0);
		buildLevel("assets/Map/ground1.jpg", textureManager, 1);
		buildLevel("assets/Map/ground2.jpg", textureManager, 2);
		buildLevel("assets/Map/ground3.jpg", textureManager, 3);
	}

	void Map::addCube(glm::ivec3 position, const Texture &text){
		CubeAtom cubeAtom;
		cubeAtom.position = glm::vec3(position);
		cubeAtom.tex_id = text.getId();
		destructibleCube.push_back(cubeAtom);
	}

	bool Map::destroyCube(glm::ivec3 position){
		int i = 0;
		for(auto& cube : destructibleCube) {
			i++;

			if(	cube.position.x == position.x &&
					cube.position.y == position.y &&
					cube.position.z == position.z
				){

					destructibleCube.erase(destructibleCube.begin() + i);
					return true;
				}
    	}
    	return false;
	}
	
	void Map::display(
        glm::mat4 ProjMatrix,
        Player& player,
        glm::mat4 MVMatrix,
        GLint uMVMatrix,
        GLint uNormalMatrix,
        GLint uMVPMatrix,
        GLint uTexture,
        TextureManager& textureManager
    ) {
    	float boundingCircleRadius = 50.0f;
    	float squareBoundingCircleRadius = boundingCircleRadius*boundingCircleRadius;

    	glm::vec3 playerPosition = player.getPosition();

    	// only display the cubes located within a radius of 20
        for(auto& cube : undestructibleCube) {
        	float xDiff = cube.position[0] - playerPosition[0];
        	float yDiff = cube.position[2] - playerPosition[2];

        	float squareDistanceToCube = xDiff*xDiff + yDiff*yDiff;
        	if(squareDistanceToCube < squareBoundingCircleRadius) {
        		Cube::display(
        			cube.position,
        			cube.tex_id,
        			ProjMatrix,
        			player.getCamera(),
        			MVMatrix,
        			uMVMatrix,
        			uNormalMatrix,
        			uMVPMatrix,
        			uTexture
        		);
        	}
        }

        for(auto& cube : destructibleCube) {
        	float xDiff = cube.position[0] - playerPosition[0];
        	float yDiff = cube.position[2] - playerPosition[2];

        	float squareDistanceToCube = xDiff*xDiff + yDiff*yDiff;
        	if(squareDistanceToCube < squareBoundingCircleRadius) {
        		Cube::display(
        			cube.position,
        			cube.tex_id,
        			ProjMatrix,
        			player.getCamera(),
        			MVMatrix,
        			uMVMatrix,
        			uNormalMatrix,
        			uMVPMatrix,
        			uTexture
        		);
        	}
        }
	}

		void Map::collidePlayerWithCube(Player& player, CubeAtom& cube, glm::vec3 deltaMove) {
			glm::vec3 playerPosition = player.getPosition();
			float minX = playerPosition[0] - player.getWidth()/2.f;
			float minY = playerPosition[2] - player.getWidth()/2.f;
			float minZ = playerPosition[1] - 1;
			float maxX = minX + player.getWidth();
			float maxY = minY + player.getWidth();
			float maxZ = minZ + player.getHeight();
			int cMinX = cube.position[0] - 0.5f;
			int cMinY = cube.position[2] - 0.5f;
			int cMinZ = cube.position[1] - 0.5f;
			int cMaxX = cMinX + 1;
			int cMaxY = cMinY + 1;
			int cMaxZ = cMinZ + 1;
			if(minZ <= cMaxZ) {
				if(
				maxX > cMinX &&
				minX < cMaxX &&
				maxY > cMinY &&
				minY < cMaxY
				) {
					playerPosition[2] = cMaxZ + 1;
					player.setPosition(playerPosition);
				}
			}
		}
	void Map::collidePlayerWithCubes(Player& player, std::vector<CubeAtom>& cubes, glm::vec3 deltaMove) {
		for(auto& cube : cubes) {
			collidePlayerWithCube(player, cube, deltaMove);
		}
	}
	void Map::collidePlayer(Player& player, glm::vec3 deltaMove) {
		collidePlayerWithCubes(player, destructibleCube, deltaMove);
		collidePlayerWithCubes(player, undestructibleCube, deltaMove);
	}
}