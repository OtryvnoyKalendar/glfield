#pragma once

const int disableCounterValue = -1;

class Counter {
public:
	Counter(const int max);
	Counter() = delete;

	bool operator()();
	int GetValue() const;
	int GetMax() const;
	bool GetEnable() const;
private:
	int maxValue{1};
	int curValue{0};
	bool enable;
};

