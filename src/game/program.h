#pragma once

class Program {
public:
	bool IsRunning();
	void UpdateLogic();
	void RenderGraphics();
	void InitProgram();
	void SelectShape();

	Program();
	~Program();
private:
	bool running = true;

	void Close();
	void CheckMainEvents();
};

