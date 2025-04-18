#pragma once

#include "../MediaSourceExamplePlugin.h"

class MediaSourceExamplePluginGUI final
	: public AK::Wwise::Plugin::PluginMFCWindows<>
	, public AK::Wwise::Plugin::GUIWindows
	, public AK::Wwise::Plugin::RequestHost
	, public AK::Wwise::Plugin::RequestObjectMedia
{
public:
	MediaSourceExamplePluginGUI() = default;

	// AK::Wwise::Plugin::GUIWindows
	virtual bool GetDialog(AK::Wwise::Plugin::eDialog in_eDialog, UINT& out_uiDialogID, AK::Wwise::Plugin::PopulateTableItem*& out_pTable) const override;
	virtual bool WindowProc(AK::Wwise::Plugin::eDialog in_eDialog, HWND in_hWnd, UINT in_message, WPARAM in_wParam, LPARAM in_lParam, LRESULT& out_lResult) override;

	// AK::Wwise::Plugin::Notifications::ObjectMedia
	virtual void NotifyPluginMediaChanged() override;

private:
	void OnLoadMediaButtonClicked();
	void RefreshMediaNameWidget();

	HWND m_hwndSettingsDialog = NULL;
};
