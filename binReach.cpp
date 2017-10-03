#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/sizer.h>

#include <iostream>
#include <cassert>
#include <string>

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
    SetEvtHandlerEnabled(true);
    Create(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150));
  }

  void OnChar(wxKeyEvent & event)
  {
    std::cout << "In ReachItFrame.. onChar" << std::endl;
    event.Skip();
  }

  void OnExit(wxCommandEvent& WXUNUSED(event))
  {
    std::cout << "Onexit " << std::endl;
  }

  wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(ReachItFrame, wxFrame)
  EVT_MENU(wxID_EXIT, ReachItFrame::OnExit)
  EVT_CHAR(ReachItFrame::OnChar)
  EVT_KEY_DOWN(ReachItFrame::OnChar)
wxEND_EVENT_TABLE()

class ReachItPanel : public wxPanel
{
  static std::string name;
public:
  ReachItPanel(wxWindow *parent) : wxPanel(parent)
  {
    name = "ReachItPanel";
    std::cout << "In ReachItPanel : " << std::endl;
    SetEvtHandlerEnabled(true);
    Connect(wxEVT_CHAR, wxKeyEventHandler(ReachItPanel::OnChar), NULL, this);
  }

  virtual ~ReachItPanel() {}

  void OnChar(wxKeyEvent& event)
  {
    std::cout << "In ReachItPanel OnChar : " << event.GetKeyCode() << std::endl;
    if ((event.GetKeyCode() == WXK_LEFT)
    ||  (event.GetKeyCode() == WXK_RIGHT))
    {
      wxWindow *child = static_cast<wxWindow*>(event.GetEventObject());
      const wxWindowList & children = this->GetChildren();
      int pos = children.IndexOf(child);
      std::cout << "Found at position : " << pos << " child : " << child << " this " << this << std::endl;
      assert ((pos != wxNOT_FOUND) && ((unsigned int)pos < children.size()) && (pos >= 0) && (children.size() > 0));
      int delta = (WXK_LEFT == event.GetKeyCode()) ? -1 : 1;
      int nextPos = (pos + delta) % children.size();
      children.Item(nextPos)->GetData()->SetFocus();
    }
  }
};

std::string ReachItPanel::name = "ReachItPanel";

class ReachItButton : public wxButton
{
public:
  ReachItButton(wxWindow* reachIt, wxWindowID id, const wxString & label) : wxButton(reachIt, id, label)
  {
  }

  void OnChar(wxKeyEvent & event)
  {
    std::cout << "In ReachItButton.. onChar" << std::endl;
    if ((event.GetKeyCode() == WXK_LEFT)
    ||  (event.GetKeyCode() == WXK_RIGHT))
    {
      // Let it go to parent.
      event.ResumePropagation(999);
      event.Skip();
    }
  }

  wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(ReachItButton, wxButton)
  EVT_CHAR(ReachItButton::OnChar)
wxEND_EVENT_TABLE()

class MyApp : public wxApp
{
public:
  bool OnInit()
  {
    wxLog* logger = new wxLogStream(&std::cout);
    wxLog::SetActiveTarget(logger);

    // wxLog::SetActiveTarget( new wxLogStderr );
    wxLog::AddTraceMask( wxTRACE_Messages );
    wxLog::AddTraceMask( wxT("keyevent") );
    // wxLog::SetTraceMask( wxTraceMessages );
    wxLog::SetVerbose( true );

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

    // Initial view.
    reachIt->SetSizerAndFit(sizer);
    sizer->Layout();
    reachIt->Layout();

    // create panel in place of second button.
    ReachItPanel *panel = new ReachItPanel(reachIt);
    ReachItPanel *innerPanel = new ReachItPanel(panel);
    ReachItButton *button5 = new ReachItButton(innerPanel, wxID_ANY, wxString::FromAscii("5"));
    ReachItButton *button6 = new ReachItButton(innerPanel, wxID_ANY, wxString::FromAscii("5"));
    ReachItButton *button7 = new ReachItButton(innerPanel, wxID_ANY, wxString::FromAscii("5"));
    ReachItButton *button8 = new ReachItButton(innerPanel, wxID_ANY, wxString::FromAscii("5"));
    wxGridSizer *innerPanelSizer = new wxGridSizer(2,2,0,0);
    innerPanelSizer->Add(button5, wxSizerFlags().Expand());
    innerPanelSizer->Add(button6, wxSizerFlags().Expand());
    innerPanelSizer->Add(button7, wxSizerFlags().Expand());
    innerPanelSizer->Add(button8, wxSizerFlags().Expand());
    innerPanel->SetSizerAndFit(innerPanelSizer);

    wxStaticBox *box1 = new wxStaticBox(panel, wxID_ANY, wxString::FromAscii("5b1"));
    wxStaticBox *box2 = new wxStaticBox(panel, wxID_ANY, wxString::FromAscii("5b2"));
    wxStaticBox *box3 = new wxStaticBox(panel, wxID_ANY, wxString::FromAscii("5b3"));

    wxGridSizer *panelSizer = new wxGridSizer(2,2,0,0);
    panelSizer->Add(innerPanel, wxSizerFlags().Expand());
    panelSizer->Add(box1, wxSizerFlags().Expand());
    panelSizer->Add(box2, wxSizerFlags().Expand());
    panelSizer->Add(box3, wxSizerFlags().Expand());

    panel->SetSizerAndFit(panelSizer);

    // Replace button2 with panel.
    sizer->Replace(button2, panel, false);
    button2->Hide();
    sizer->Layout();
    reachIt->Layout();

    // Replace panel with button2
    // sizer->Replace(panel, button2, false);
    // panel->Hide();
    // button2->Show();
    // sizer->Layout();
    // reachIt->Layout();

    // button3->SetFocus();
    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
