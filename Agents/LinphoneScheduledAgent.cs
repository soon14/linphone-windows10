﻿using Microsoft.Phone.Networking.Voip;
using Microsoft.Phone.Scheduler;
using Linphone.BackEnd;
using Linphone.BackEnd.OutOfProcess;
using System.Diagnostics;
using System.IO;
using System.Xml.Serialization;
using System;

namespace Linphone.Agents
{
    public class LinphoneScheduledAgent : ScheduledTaskAgent
    {
        // Indicates if this agent instance is handling an incoming call or not
        private bool isIncomingCallAgent;

        public LinphoneScheduledAgent()
        {

        }

        protected override void OnInvoke(ScheduledTask task)
        {
            Debug.WriteLine("[LinphoneScheduledAgent] ScheduledAgentImpl has been invoked with argument of type {0}.", task.GetType());

            Globals.Instance.StartServer(RegistrationHelper.OutOfProcServerClassNames);

            VoipHttpIncomingCallTask incomingCallTask = task as VoipHttpIncomingCallTask;
            if (incomingCallTask != null)
            {
                this.isIncomingCallAgent = true;

                String message = System.Text.Encoding.UTF8.GetString(incomingCallTask.MessageBody, 0, incomingCallTask.MessageBody.Length);
                Debug.WriteLine("[LinphoneScheduledAgent] Received VoIP Incoming Call task with body {0}", message);
                //TODO Parse the the incoming push notification message 
                String callerName = "", callerNumber = "";
                Debug.WriteLine("[{0}] Incoming call from caller {1}, number {2}", "KeepAliveAgent", callerName, callerNumber);

                // Initiate incoming call processing 
                // If you want to pass in additional information such as pushNotification.Number, you can 
                bool incomingCallProcessingStarted = BackEnd.Globals.Instance.CallController.OnIncomingCallReceived(callerName, callerNumber, this.OnIncomingCallDialogDismissed);

                if (!incomingCallProcessingStarted)
                {
                    // For some reasons, the incoming call processing was not started. 
                    base.NotifyComplete();
                    return;
                }
            }
            else
            {
                VoipKeepAliveTask keepAliveTask = task as VoipKeepAliveTask;
                if (keepAliveTask != null)
                {
                    this.isIncomingCallAgent = false;

                    base.NotifyComplete();
                }
                else
                {
                    throw new InvalidOperationException(string.Format("Unknown scheduled task type {0}", task.GetType()));
                }
            }
        }

        private void OnIncomingCallDialogDismissed()
        {
            Debug.WriteLine("[IncomingCallAgent] Incoming call processing is now complete.");

            base.NotifyComplete();
        }

        protected override void OnCancel()
        {
            Debug.WriteLine("[{0}] Cancel requested.", this.isIncomingCallAgent ? "IncomingCallAgent" : "KeepAliveAgent");

            base.NotifyComplete();
        }
    }
}
