#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/sizer.h>

#include <iostream>
#include <cassert>
#include <string>
#include <map>

class ReachItFrame : public wxFrame
{
public:
  ReachItFrame(const wxString& title) : wxFrame()
  {
    Create(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150));
  }

  virtual ~ReachItFrame() {}

  void OnChar(wxKeyEvent & event)
  {
    wxLogMessage("mylog %s", "In ReachItFrame.. onChar");

    switch (event.GetKeyCode())
    {
      case WXK_RETURN:
        this->Iconize(true);
        break;
    }
  }
  wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(ReachItFrame, wxFrame)
  EVT_CHAR(ReachItFrame::OnChar)
wxEND_EVENT_TABLE()

class ReachItButton : public wxButton
{
public:
  ReachItButton(wxWindow* reachIt, wxWindowID id, const wxString & label)
  : wxButton(reachIt, id, label, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS)
  {
  }

  virtual ~ReachItButton() {}

  void OnChar(wxKeyEvent & event)
  {
    wxLogMessage("mylog %s keycode : %d", "In ReachItButton.. onChar", event.GetKeyCode());

    switch (event.GetKeyCode())
    {
      case WXK_RETURN:
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

  void OnSetFocus(wxFocusEvent & event)
  {
    // move the cursor to the top of this button.
    this->WarpPointer(0, 0);
  }

  wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(ReachItButton, wxButton)
  EVT_CHAR(ReachItButton::OnChar)
  EVT_SET_FOCUS(ReachItButton::OnSetFocus)
wxEND_EVENT_TABLE()

class ReachItPanel : public wxPanel
{
  std::map<ReachItPanel*, ReachItButton*> hiddenButtons;

public:

  ReachItPanel(wxWindow *parent) : wxPanel(parent)
  {
    wxLogMessage("mylog %s", "In ReachItPanel : ");

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
    // ReachIt mode off..
    if (event.GetKeyCode() == WXK_RETURN)
    {
      event.Skip(); // let the parent frame handle it.
      return;
    }

    wxLogMessage("mylog %s %d", "In ReachItPanel OnChar : ", event.GetKeyCode());
    ReachItButton *childButton = static_cast<ReachItButton*>(event.GetEventObject());
    const wxWindowList & children = this->GetChildren();
    int pos = children.IndexOf(childButton);
    wxLogMessage("mylog Found at position : %d : childButton : %p : this : %p ", pos, childButton, this);
    assert ((pos != wxNOT_FOUND) && ((unsigned int)pos < children.size()) && (pos >= 0) && (children.size() > 0));

    if ((event.GetKeyCode() == WXK_LEFT)
    ||  (event.GetKeyCode() == WXK_RIGHT))
    {
      int nextPos = (WXK_LEFT == event.GetKeyCode()) ? nextAntiClockWisePos(pos) : nextClockWisePos(pos) ;
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
        if (it.second == childButton) // in case, user used mouse
        {
          this->GetSizer()->Replace(it.first, newPanel, false);
          it.first->Destroy();
          this->GetSizer()->Layout();
          hiddenButtons.erase(it.first);
        }
      }
      hiddenButtons[newPanel] = childButton;

      // set focus on first child of newPanel.
      newPanel->GetChildren().Item(0)->GetData()->SetFocus();
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
    wxLogMessage("mylog In moveup.. : this : %p : childPanel : %p", this, childPanel);
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
    return -1; // for compiler warning.
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
    return -1; // for compiler warning.
  }

  // on focus on panel, move the focus to first visible button.
  // void OnSetFocus(wxFocusEvent & event)
  // {
  //   wxLogMessage("mylog : ReachItPanel : OnSetFocus : ");

  //   if (hiddenButtons.size() > 0)
  //   {
  //     hiddenButtons.begin()->first->OnSetFocus(event);
  //   }
  //   else
  //   {
  //     this->GetChildren().Item(0)->GetData()->SetFocus();
  //   }
  // }

  wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(ReachItPanel, wxPanel)
  EVT_CHAR(ReachItPanel::OnChar)
  // EVT_SET_FOCUS(ReachItPanel::OnSetFocus)
wxEND_EVENT_TABLE()

class MyApp : public wxApp
{
public:
  virtual bool OnInit()
  {
    if ( !wxApp::OnInit() )
      return false;

    wxLog* logger = new wxLogStream(&std::cout);
    wxLog::SetActiveTarget(logger);

    wxLog::AddTraceMask( wxTRACE_Messages );
    wxLog::AddTraceMask( wxT("keyevent") );
    wxLog::AddTraceMask( wxT("mylog") );
    wxLog::SetVerbose( true );

    ReachItFrame *reachIt = new ReachItFrame(wxT("ReachIt"));
    // Show full screen transparent window.
    reachIt->Show(true);
    assert(reachIt->SetTransparent(150));
    assert(reachIt->ShowFullScreen(true, wxFULLSCREEN_ALL));

    new ReachItPanel(reachIt);

    // Hack for bug windows : Initial layout does not happen properly and
    // four buttons come at the top of window taking small space.
    reachIt->Iconize(true);
    reachIt->Iconize(false);

    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
