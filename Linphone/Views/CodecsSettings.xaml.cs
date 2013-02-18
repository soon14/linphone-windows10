﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using Linphone.Resources;
using Linphone.Model;

namespace Linphone.Views
{
    /// <summary>
    /// Page displaying each available codec along as a switch to let the user enabling/disabling them.
    /// </summary>
    public partial class CodecsSettings : BasePage
    {
        private SettingsManager _appSettings = new SettingsManager();

        /// <summary>
        /// Public constructor.
        /// </summary>
        public CodecsSettings()
        {
            InitializeComponent();
            BuildLocalizedApplicationBar();

            AMRNB.IsChecked = _appSettings.AMRNB;
            AMRWB.IsChecked = _appSettings.AMRWB;
            Speex16.IsChecked = _appSettings.Speex16;
            Speex8.IsChecked = _appSettings.Speex8;
            PCMU.IsChecked = _appSettings.PCMU;
            PCMA.IsChecked = _appSettings.PCMA;
            G722.IsChecked = _appSettings.G722;
            ILBC.IsChecked = _appSettings.ILBC;
            SILK16.IsChecked = _appSettings.SILK16;
            GSM.IsChecked = _appSettings.GSM;
        }

        private void cancel_Click_1(object sender, EventArgs e)
        {
            NavigationService.GoBack();
        }

        private void save_Click_1(object sender, EventArgs e)
        {
            _appSettings.AMRNB = AMRNB.IsChecked;
            _appSettings.AMRWB = AMRWB.IsChecked;
            _appSettings.Speex16 = Speex16.IsChecked;
            _appSettings.Speex8 = Speex8.IsChecked;
            _appSettings.PCMU = PCMU.IsChecked;
            _appSettings.PCMA = PCMA.IsChecked;
            _appSettings.PCMA = PCMA.IsChecked;
            _appSettings.G722 = G722.IsChecked;
            _appSettings.ILBC = ILBC.IsChecked;
            _appSettings.SILK16 = SILK16.IsChecked;
            _appSettings.GSM = GSM.IsChecked;

            NavigationService.GoBack();
        }

        private void BuildLocalizedApplicationBar()
        {
            ApplicationBar = new ApplicationBar();

            ApplicationBarIconButton appBarSave = new ApplicationBarIconButton(new Uri("/Assets/AppBar/save.png", UriKind.Relative));
            appBarSave.Text = AppResources.SaveSettings;
            ApplicationBar.Buttons.Add(appBarSave);
            appBarSave.Click += save_Click_1;

            ApplicationBarIconButton appBarCancel = new ApplicationBarIconButton(new Uri("/Assets/AppBar/cancel.png", UriKind.Relative));
            appBarCancel.Text = AppResources.CancelChanges;
            ApplicationBar.Buttons.Add(appBarCancel);
            appBarCancel.Click += cancel_Click_1;
        }
    }
}