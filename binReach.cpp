#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/string.h>

#include <iostream>
#include <cassert>

class ReachItFrame : public wxFrame
{
public:
  ReachItFrame(const wxString& title) : wxFrame()
  {
    Create(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150));
  }
};

class MyApp : public wxApp
{
public:
  bool OnInit()
  {
    ReachItFrame *reachIt = new ReachItFrame(wxT("ReachIt"));
    reachIt->Show(true);
    assert(reachIt->SetTransparent(150));
    assert(reachIt->ShowFullScreen(true, wxFULLSCREEN_ALL));

    wxPanel *panel = new wxPanel(reachIt);
    wxGridSizer *sizer = new wxGridSizer(2, 2, 0, 0);

    wxButton *button = new wxButton(panel, wxID_ANY, wxString::FromAscii("1"));
    sizer->Add(button, wxSizerFlags().Expand());

    button = new wxButton(panel, wxID_ANY, wxString::FromAscii("2"));
    sizer->Add(button, wxSizerFlags().Expand());

    button = new wxButton(panel, wxID_ANY, wxString::FromAscii("3"));
    sizer->Add(button, wxSizerFlags().Expand());

    button = new wxButton(panel, wxID_ANY, wxString::FromAscii("4"));
    sizer->Add(button, wxSizerFlags().Expand());

    panel->SetSizerAndFit(sizer);

    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
