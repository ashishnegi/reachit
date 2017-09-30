#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/sizer.h>
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

    wxGridSizer *sizer = new wxGridSizer(2, 2, 4, 4);

    wxGrid *grid = new wxGrid(simple, -1); //, wxPoint(0,0), wxSize(400,300));
    grid->CreateGrid(2,2);
    sizer->Add(grid, wxSizerFlags().Expand().Border(wxALL, 2));

    grid = new wxGrid(simple, -1); //, wxPoint(0,0), wxSize(400,300));
    grid->CreateGrid(2,2);
    sizer->Add(grid, wxSizerFlags().Expand().Border(wxALL, 2));

    grid = new wxGrid(simple, -1); //, wxPoint(0,0), wxSize(400,300));
    grid->CreateGrid(2,2);
    sizer->Add(grid, wxSizerFlags().Expand().Border(wxALL, 2));

    grid = new wxGrid(simple, -1); //, wxPoint(0,0), wxSize(400,300));
    grid->CreateGrid(2,2);
    sizer->Add(grid, wxSizerFlags().Expand().Border(wxALL, 2));

    simple->SetSizerAndFit(sizer);

    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
