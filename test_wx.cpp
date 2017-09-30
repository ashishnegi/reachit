#include <wx/wx.h>
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
    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
