#pragma once

class Program {
private:
	bool running = true;

	void Close();
	void CheckMainEvents();
public:
	bool GetRunning();
	void UpdateProgramLogic();
	void RenderGraphics();
	void InitProgram();

	Program();
	~Program();
};

