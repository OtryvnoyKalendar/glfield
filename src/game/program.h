#pragma once

class Program {
public:
	bool IsRunning();
	void UpdateLogic();
	void InitScene();

	Program();
	~Program() = default;
private:
	bool running{true};

	void InitProgram();
	void Close();
	void CheckMainEvents();
	void SelectShape();
	void RenderGraphics();
};

