#include "Game.h"

void Game::startup() {
	Shader vertex = { GL_VERTEX_SHADER, "vertex.glsl" };
	Shader fragment = { GL_FRAGMENT_SHADER, "fragment.glsl" };
	program.addShader({ vertex, fragment });

	glEnable(GL_DEPTH_TEST);

	program.useProgram();

	// Bind the program with the blocks
	Block::setProgramId(program.getProgram());

	(player.physics.node)->position = glm::vec3(20.0f, 10.0f, 45.0f);
	player.SetInputManager(inputManager);
	player.camera.setRatio(window.getWindowRatio());
}

void Game::render(double delta) {
	// We only have one program so this is fine for now

	static const GLfloat color[] = { 0.6f, 0.7f, 0.5f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
	glClear(GL_DEPTH_BUFFER_BIT);

	world.render(delta);
	player.Update(delta);
}

void Game::update(double delta) {
	world.update(delta);

	glm::mat4 cameraMatrix = player.camera.getCameraMatrix();
	GLuint cameraMatrixLoc = program.getUniformLocation("cameraMatrix");
	glUniformMatrix4fv(cameraMatrixLoc, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Game::shutdown() {

}

