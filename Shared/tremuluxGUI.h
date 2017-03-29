/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_369E4FABD7B7EAB2__
#define __JUCE_HEADER_369E4FABD7B7EAB2__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "tremulux_include.h"
#include "../../calib/include/blocks/Oscillator.h"
#include "../../calib/include/blocks/Filter.h"
#include <array>



//#include "flatLookAndFeel.h"


using namespace tremulux;

class TremuluxCore;


//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TremuluxGUI  : public Component,
                     public Timer,
                     public ModalComponentManager,
                     public ActionListener,
                     private DrawableButton::Listener,
                     private Slider::Listener,
                     private ComboBox::Listener,
                     public LabelListener
{
public:
    //==============================================================================
    TremuluxGUI (TremuluxCore* backend);
    ~TremuluxGUI();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    friend class TremuluxCore;

    void synchronizeState();

    TremuluxCore* getCore() const;

    void showComponent(Component* componentToDisplay);

    void hideComponent();

    //==============================================================================
    void userTriedToCloseWindow() override;

    void buttonClicked(Button* button) override;

    void buttonStateChanged(Button* button) override;

    void sliderValueChanged(Slider* slider) override;

    void comboBoxChanged (ComboBox* box) override;

    void editorShown (Label* textBox, TextEditor& textEditor) override;

    void editorHidden(Label* textBox, TextEditor& textEditor) override;

    void labelTextChanged(Label* textBox) override;

    static void alertCallback(int modalResult, String context);

    void timerCallback() override;
    void setRateDialRanges(const float max);

    void visibilityChanged() override;

    void actionListenerCallback (const String& message) override;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    TremuluxCore* core;

    //////
    // GUI
    FlatLookAndFeel lookAndFeel;
    ScopedPointer<Component> curtain;
    ScopedPointer<Component> subWindow;


    // used for spinning GUI indicator
    Atomic<int32> * waitFlag;

    ///////////
    // Buttons

    ScopedPointer<DrawableButton> openButton;
    ScopedPointer<DrawableButton> saveButton;

    ScopedPointer<DrawableButton> bypassButton;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> bypassButtonAttachment;

    std::array<ScopedPointer<DrawableButton>, NUM_MODS> syncToggleButtons;
    std::array<ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment>, NUM_MODS> syncToggleButtonAttachments;

    /////////////////////
    // Sliders and Labels

    std::array<ScopedPointer<CustomSlider>, NUM_MODS> hzRateDials;
    std::array<ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>, NUM_MODS> hzRateDialAttachments;
    std::array<ScopedPointer<CustomSlider>, NUM_MODS> syncedRateDials;
    std::array<ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>, NUM_MODS> syncedRateDialAttachments;
    std::array<ScopedPointer<Label>, NUM_MODS> rateLabels;

    std::array<ScopedPointer<CustomSlider>, NUM_MODS> depthDials;
    std::array<ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>, NUM_MODS> depthDialAttachments;
    std::array<ScopedPointer<Label>, NUM_MODS> depthLabels;

    ScopedPointer<CustomSlider> mixDial;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mixDialAttachment;
    ScopedPointer<Label> mixLabel;

    ScopedPointer<CustomSlider> gainDial;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainDialAttachment;
    ScopedPointer<Label> gainLabel;

    ScopedPointer<CustomSlider> blendDial;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendDialAttachment;
    ScopedPointer<Label> blendLabel;


    //////
    // Etc
    Button* lastButtonClicked;

    // Private Functions & Classes
    void displayRateDial(const unsigned int oscillatorID, const bool synced);

    void updateButtonStates();

    void clearOtherToggleStates(Button* button);

    class SubWindow : public Component
    {
    public:
        SubWindow(TremuluxGUI* parent);

        ~SubWindow();

    private:
        void paint(Graphics& g) override;

        TremuluxGUI* owner;
    };

    class Curtain : public Component
    {
    public:
        Curtain(TremuluxGUI* parent);

        ~Curtain();

    private:
        void paint(Graphics& g) override;

        void mouseUp(const MouseEvent& e) override;

        TremuluxGUI* owner;
    };

    class ModalWaitAnimation  : public Thread, private Timer
    {
    public:

        ModalWaitAnimation (TremuluxGUI* parent, const Rectangle<int>& sizeAndPosition,
                            Atomic<int32>* &terminateFlag,
                            void (TremuluxGUI::*callback)(void) = nullptr,
                            const int cancellingTimeOutMs = 1000,
                            const String& waitingText = "", const String& completeText = "");

        ~ModalWaitAnimation();

#if JUCE_MODAL_LOOPS_PERMITTED
        /** Starts the thread and waits for it to finish.

         This will start the thread, make the dialog box appear, and wait until either
         the thread finishes normally, or until the cancel button is pressed.

         Before returning, the dialog box will be hidden.

         @param priority   the priority to use when starting the thread - see
         Thread::startThread() for values
         @returns true if the thread finished normally; false if the user pressed cancel
         */
        bool runThread(int priority = 5);
#endif

        void launchThread(int priority = 5);

        void run() override;

        void timerCallback() override;

        // This method gets called on the message thread once our thread has finished..
        void threadComplete(bool userPressedCancel);

        void setStatusMessage(const String& newStatusMessage);

        void setCondition(Atomic<int32>& terminateFlag);

    private:
        TremuluxGUI* owner;

        double progress;
        String message;
        const String waitingMessage;
        const String completeMessage;

        Atomic<int32>*& condition;
        void (TremuluxGUI::*onFinish)(void);
        const int timeOutMsWhenCancelling;
        bool wasCancelledByUser;
        CriticalSection messageLock;

        ScopedPointer<ProgressBar> progressBar;
    };



    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TremuluxGUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_369E4FABD7B7EAB2__
