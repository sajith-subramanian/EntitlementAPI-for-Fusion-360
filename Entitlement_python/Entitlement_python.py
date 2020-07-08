#Author-Sajith Subramanian
#Description-

import adsk.core, adsk.fusion, adsk.cam, traceback
from .modules import requests
import json

def run(context):
    ui = None
    try:
        app = adsk.core.Application.get()
        ui  = app.userInterface
        userId = app.userId
        appId ="1006119760063675415"
        url  = "https://apps.exchange.autodesk.com/webservices/checkentitlement" + "?userid=" + userId + "&appid=" + appId
        r = requests.get(url)
        #ui.messageBox(r.text)
        #json1 = r.json()
        resp_dict = json.loads(r.text)
        val = resp_dict.get('IsValid')
      
        if val:
            ui.messageBox("IsValid is True")
        else:
            ui.messageBox("IsValid is False")

    except:
        if ui:
            ui.messageBox('Failed:\n{}'.format(traceback.format_exc()))

def stop(context):
    ui = None
    try:
        app = adsk.core.Application.get()
        ui  = app.userInterface
        ui.messageBox('Stop addin')

    except:
        if ui:
            ui.messageBox('Failed:\n{}'.format(traceback.format_exc()))
