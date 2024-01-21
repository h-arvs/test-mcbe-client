#pragma once

class Cancellable {
	bool cancelled = false;
public:
	bool isCancelled() {
		return this->cancelled;
	}

	void cancel() {
		this->cancelled = true;
	}

	void unCancel() {
		this->cancelled = false;
	}
};