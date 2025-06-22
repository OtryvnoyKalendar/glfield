#pragma once

class Program {
public:
	bool IsRunning();
	void UpdateLogic();
	void InitProgram();

	Program();
	~Program() = default;
private:
	bool running{true};

	void Close();
	void CheckMainEvents();
	void SelectShape();
	void RenderGraphics();
};

