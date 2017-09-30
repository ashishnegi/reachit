#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/string.h>

#include <iostream>
#include <cassert>

class Simple : public wxFrame
{
public:
  Simple(const wxString& title) : wxFrame()
  {
    Create(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150));
  }
};

class MyApp : public wxApp
{
public:
  bool OnInit()
  {
    Simple *simple = new Simple(wxT("Simple"));
    simple->Show(true);
    assert(simple->SetTransparent(150));
    assert(simple->ShowFullScreen(true, wxFULLSCREEN_ALL));

    wxPanel *panel = new wxPanel(simple);
    wxGridSizer *sizer = new wxGridSizer(2, 2, 0, 0);

    wxStaticText *text = new wxStaticText(panel, wxID_ANY, wxString::FromAscii("1"));
    sizer->Add(text, wxSizerFlags().Expand().Border(wxRIGHT, 1));

    text = new wxStaticText(panel, wxID_ANY, wxString::FromAscii("2"));
    sizer->Add(text, wxSizerFlags().Expand().Border(wxBOTTOM, 1));

    text = new wxStaticText(panel, wxID_ANY, wxString::FromAscii("3"));
    sizer->Add(text, wxSizerFlags().Expand().Border(wxUP, 1));

    text = new wxStaticText(panel, wxID_ANY, wxString::FromAscii("4"));
    sizer->Add(text, wxSizerFlags().Expand().Border(wxLEFT, 1));

    panel->SetSizerAndFit(sizer);

    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
