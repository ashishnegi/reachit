#include <wx/wx.h>
#include <iostream>
#include <cassert>

class Simple : public wxFrame
{
public:
    Simple(const wxString& title)
		: wxFrame()
	{
		Create(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150));
		Centre();
	}
};

class MyApp : public wxApp
{
public:
	bool OnInit()
	{
		Simple *simple = new Simple(wxT("Simple"));
		simple->Show(true);
		if (simple->SetTransparent(150))
		{
			std::cout << "Able to set transparent..\n";
		}
		else
		{
			std::cout << "Not able to set transparent..\n";
		}
		return true;
	}
};

wxIMPLEMENT_APP(MyApp);
