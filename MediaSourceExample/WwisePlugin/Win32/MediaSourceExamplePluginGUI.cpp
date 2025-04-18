#include "MediaSourceExamplePluginGUI.h"
#include "../resource.h"
#include "../../MediaSourceExampleConfig.h"

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#include "afxwin.h"
#include "afxext.h"

bool MediaSourceExamplePluginGUI::GetDialog(AK::Wwise::Plugin::eDialog in_eDialog, UINT& out_uiDialogID, AK::Wwise::Plugin::PopulateTableItem*& out_pTable) const
{
	switch (in_eDialog)
	{
	case AK::Wwise::Plugin::SettingsDialog:
		out_uiDialogID = IDD_MEDIASOURCEPLUGIN_BIG;
		out_pTable = NULL;
		return true;
	}
	return false;
}

bool MediaSourceExamplePluginGUI::WindowProc(AK::Wwise::Plugin::eDialog in_eDialog, HWND in_hWnd, UINT in_message, WPARAM in_wParam, LPARAM in_lParam, LRESULT& out_lResult)
{
	switch (in_message)
	{
	case WM_INITDIALOG:
	{
		if (in_eDialog == AK::Wwise::Plugin::SettingsDialog)
		{
			m_hwndSettingsDialog = in_hWnd;
			RefreshMediaNameWidget();
		}
		break;
	}
	case WM_DESTROY:
	{
		if (in_eDialog == AK::Wwise::Plugin::SettingsDialog)
		{
			m_hwndSettingsDialog = NULL;
		}
		break;
	}


	case WM_COMMAND:
	{
		switch (HIWORD(in_wParam))
		{
		case BN_CLICKED:
		{
			switch (LOWORD(in_wParam))
			{
			case IDC_BTN_LOAD_MEDIA:
				OnLoadMediaButtonClicked();
				return true;
			}
			break;
		}
		}
		break;
	}
	}
	return false;
}

void MediaSourceExamplePluginGUI::NotifyPluginMediaChanged()
{
	RefreshMediaNameWidget();
}

void MediaSourceExamplePluginGUI::OnLoadMediaButtonClicked()
{
	CFileDialog dialog(/*bOpenFileDialog*/ true, NULL, NULL, OFN_HIDEREADONLY, _T("Wave Files (*.wav)|*.wav|"));
	if (dialog.DoModal() == IDOK)
	{
		m_objectMedia.SetMediaSource(dialog.GetPathName(), MediaSourceExampleConfig::ExampleMediaIndex, /*Replace=*/ true);
		m_objectMedia.InvalidateMediaSource(MediaSourceExampleConfig::ExampleMediaIndex);
	}
}

void MediaSourceExamplePluginGUI::RefreshMediaNameWidget()
{
	if (m_hwndSettingsDialog != NULL)
	{
		AkOSChar FileNameBuf[_MAX_PATH];
		const uint32_t FileNameLen = m_objectMedia.GetMediaSourceFileName(FileNameBuf, _MAX_PATH, MediaSourceExampleConfig::ExampleMediaIndex);
		SetDlgItemTextW(m_hwndSettingsDialog, IDC_TEXT_MEDIA_NAME, FileNameBuf);
	}
}

AK_ADD_PLUGIN_CLASS_TO_CONTAINER(MediaSourceExample, MediaSourceExamplePluginGUI, MediaSourceExampleSource);
