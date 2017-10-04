#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/sizer.h>

#include <iostream>
#include <cassert>
#include <string>
#include <map>

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

class ReachItButton : public wxButton
{
public:
  ReachItButton(wxWindow* reachIt, wxWindowID id, const wxString & label) : wxButton(reachIt, id, label)
  {
  }

  void OnChar(wxKeyEvent & event)
  {
    wxLogTrace("mylog", "In ReachItButton.. onChar");

    switch (event.GetKeyCode())
    {
      case WXK_LEFT:
      case WXK_RIGHT:
      case WXK_UP:
      case WXK_DOWN:
      {
        // Let it go to parent.
        event.ResumePropagation(999);
        event.Skip();
        break;
      }
      default:
        break;
    }
  }

  wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(ReachItButton, wxButton)
  EVT_CHAR(ReachItButton::OnChar)
wxEND_EVENT_TABLE()

class ReachItPanel : public wxPanel
{
  std::map<ReachItPanel*, ReachItButton*> hiddenButtons;

public:

  ReachItPanel(wxWindow *parent) : wxPanel(parent)
  {
    wxLogTrace("mylog", "In ReachItPanel : ");
    SetEvtHandlerEnabled(true);
    Connect(wxEVT_CHAR, wxKeyEventHandler(ReachItPanel::OnChar), NULL, this);

    ReachItButton *button5 = new ReachItButton(this, wxID_ANY, wxString::FromAscii("5"));
    ReachItButton *button6 = new ReachItButton(this, wxID_ANY, wxString::FromAscii("5"));
    ReachItButton *button7 = new ReachItButton(this, wxID_ANY, wxString::FromAscii("5"));
    ReachItButton *button8 = new ReachItButton(this, wxID_ANY, wxString::FromAscii("5"));

    wxGridSizer *sizer = new wxGridSizer(2,2,0,0);
    sizer->Add(button5, wxSizerFlags().Expand());
    sizer->Add(button6, wxSizerFlags().Expand());
    sizer->Add(button7, wxSizerFlags().Expand());
    sizer->Add(button8, wxSizerFlags().Expand());
    this->SetSizerAndFit(sizer);
  }

  virtual ~ReachItPanel() {}

  void OnChar(wxKeyEvent& event)
  {
    wxLogTrace("mylog", "In ReachItPanel OnChar : %d", event.GetKeyCode());
    ReachItButton *childButton = static_cast<ReachItButton*>(event.GetEventObject());
    const wxWindowList & children = this->GetChildren();
    int pos = children.IndexOf(childButton);
    wxLogTrace("mylog", "Found at position : %d : childButton : %p : this : %p ", pos, childButton, this);
    assert ((pos != wxNOT_FOUND) && ((unsigned int)pos < children.size()) && (pos >= 0) && (children.size() > 0));

    if ((event.GetKeyCode() == WXK_LEFT)
    ||  (event.GetKeyCode() == WXK_RIGHT))
    {
      int nextPos = (WXK_LEFT == event.GetKeyCode()) ? nextClockWisePos(pos) : nextAntiClockWisePos(pos) ;
      children.Item(nextPos)->GetData()->SetFocus();
    }
    else
    if (event.GetKeyCode() == WXK_DOWN)
    {
      ReachItPanel *newPanel = new ReachItPanel(this);
      this->GetSizer()->Replace(childButton, newPanel, false);
      childButton->Hide();
      this->GetSizer()->Layout();
      // assert that this button is not already hidden. Should not be possible from view.
      for (auto it : hiddenButtons) {
        assert(it.second != childButton);
      }
      hiddenButtons[newPanel] = childButton;
      // TODO : set focus on the childButton of newPanel.
    }
    else
    if (event.GetKeyCode() == WXK_UP)
    {
      // ignore the childButton.
      ReachItPanel* parent = dynamic_cast<ReachItPanel*>(this->m_parent);
      if (NULL != parent) // false for topmost panel..
      {
        parent->moveUp(this);
      }
    }
  }

  void moveUp(ReachItPanel *childPanel)
  {
    wxLogTrace("mylog", "In moveup.. : this : %p : childPanel : %p", this, childPanel);
    assert(hiddenButtons.end() != hiddenButtons.find(childPanel));

    ReachItButton *hiddenButton = hiddenButtons.find(childPanel)->second;
    this->GetSizer()->Replace(childPanel, hiddenButton, false);
    childPanel->Destroy();

    hiddenButton->Show();
    this->GetSizer()->Layout();
    hiddenButton->SetFocus();
    hiddenButtons.erase(childPanel);
  }

  int nextClockWisePos(int pos)
  {
    switch (pos)
    {
      case 0 : return 1;
      case 1 : return 3;
      case 2 : return 0;
      case 3 : return 2;
      default : assert(false);
    }
  }

  int nextAntiClockWisePos(int pos)
  {
    switch (pos)
    {
      case 0 : return 2;
      case 1 : return 0;
      case 2 : return 3;
      case 3 : return 1;
      default : assert(false);
    }
  }
};

class MyApp : public wxApp
{
public:
  bool OnInit()
  {
    wxLog* logger = new wxLogStream(&std::cout);
    wxLog::SetActiveTarget(logger);

    wxLog::AddTraceMask( wxTRACE_Messages );
    wxLog::AddTraceMask( wxT("keyevent") );
    wxLog::AddTraceMask( wxT("mylog") );
    wxLog::SetVerbose( true );

    ReachItFrame *reachIt = new ReachItFrame(wxT("ReachIt"));
    reachIt->Show(true);
    assert(reachIt->SetTransparent(150));
    assert(reachIt->ShowFullScreen(true, wxFULLSCREEN_ALL));

    new ReachItPanel(reachIt);
    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
