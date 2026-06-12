#pragma once

class CHelperPlayers
{
public:
	CHelperPlayers() { this->set_hwnd(nullptr); }
	void init_dialog(const HWND hwnd);
	void set_hwnd(const HWND hwnd) { this->window_hwnd_ = hwnd; }
	void close_client();
	void search_ip();
	void clear_ip();
	void ban_ip();
	void ban_hwid();
	void list_ip(WPARAM wParam);
	void list_hwid(WPARAM wParam);
	void reload();
	void set_account_info(int index);
private:
	HWND window_hwnd_;
}; extern CHelperPlayers gHelperPlayers;