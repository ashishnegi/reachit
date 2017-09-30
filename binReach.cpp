#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/sizer.h>

#include <iostream>
#include <cassert>

class ReachItGrid : public wxGrid
{
public:
  ReachItGrid(wxWindow* parent) : wxGrid(parent, wxID_ANY)
  {
    CreateGrid(2,2);
    SetTabBehaviour(Tab_Wrap);
  }

  virtual void OnSize(wxSizeEvent & event)
  {
    wxSize clientSize = GetClientSize();

    long numCols = GetNumberCols();
    long width = clientSize.GetWidth() / numCols;
    for (long i = 0; i < numCols; ++i) {
      SetColSize(0, width);
    }

    long numRows = GetNumberRows();
    long height = clientSize.GetHeight() / numRows;
    for (long j = 0; j < numRows; ++j) {
      SetRowSize(0, height);
    }

    event.Skip();
  }

};

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
    wxGridSizer *sizer = new wxGridSizer(2, 2, 0, 0);

    wxButton *button1 = new wxButton(reachIt, wxID_ANY, wxString::FromAscii("1"));
    sizer->Add(button1, wxSizerFlags().Expand());

    wxButton *button2 = new wxButton(reachIt, wxID_ANY, wxString::FromAscii("2"));
    sizer->Add(button2, wxSizerFlags().Expand());

    wxButton *button3 = new wxButton(reachIt, wxID_ANY, wxString::FromAscii("3"));
    sizer->Add(button3, wxSizerFlags().Expand());

    wxButton *button4 = new wxButton(reachIt, wxID_ANY, wxString::FromAscii("4"));
    button4->MoveBeforeInTabOrder(button3);
    sizer->Add(button4, wxSizerFlags().Expand());

    reachIt->SetSizerAndFit(sizer);
    sizer->Layout();
    reachIt->Layout();

    // sizer->Remove(1);
    // reachIt->RemoveChild(button2);
    button2->Destroy();

    reachIt->Layout();

    wxPanel *panel = new wxPanel(reachIt);
    wxButton *button5 = new wxButton(panel, wxID_ANY, wxString::FromAscii("5"));
    wxStaticBox *box1 = new wxStaticBox(panel, wxID_ANY, wxString::FromAscii("5b1"));
    wxStaticBox *box2 = new wxStaticBox(panel, wxID_ANY, wxString::FromAscii("5b2"));
    wxStaticBox *box3 = new wxStaticBox(panel, wxID_ANY, wxString::FromAscii("5b3"));

    wxGridSizer *panelSizer = new wxGridSizer(2,2,0,0);
    panelSizer->Add(button5, wxSizerFlags().Expand());
    panelSizer->Add(box1, wxSizerFlags().Expand());
    panelSizer->Add(box2, wxSizerFlags().Expand());
    panelSizer->Add(box3, wxSizerFlags().Expand());

    panel->SetSizerAndFit(panelSizer);

    sizer->Insert(1, panel, wxSizerFlags().Expand());

    sizer->Layout();
    reachIt->Layout();
    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
