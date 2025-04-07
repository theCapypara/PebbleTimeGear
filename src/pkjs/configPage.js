// I can't for the life of me figure out how to debug custom clay components, so I'll just do it this way..
function imageGallery(config) {
  var images = "";
  config.forEach(function(item) {
      images += "" + 
        "<div class='image' style='padding-right: 15px; padding-bottom: 20px; text-align: center;'>" +
          "<div class='label' style='text-align: center;'>"+item.label+"</div>" +
          "<img src='"+item.src+"' style='width: 108px;'>" +
        "</div>";
  }); 
  return "" +
    "<div class='description' style='padding-left: 0;'>Previews</div>" +
    "<div class='gallery' style='display: flex; flex-flow: row wrap;'>" +
      images +
    "</div>";
}

module.exports = [
  { 
    "type": "heading", 
    "defaultValue": "Time Gear" 
  }, 
  {
  "type": "section",
  "items": [
    {
      "type": "heading",
      "defaultValue": "General"
    },
    {
      "type": "checkboxgroup",
      "messageKey": "CfgBackground",
      "label": "Background",
      "defaultValue": [true, true, true],
      "options": ["Background 1", "Background 2", "Background 3"]
    },
    {
      "type": "slider",
      "messageKey": "CfgBackgroundCycleInterval",
      "defaultValue": 60,
      "label": "Background Cycle Interval",
      "description": "The watch will cycle all selected backgrounds in this interval (minutes). Due to memory limitations, the image will only update if the watchface gets reloaded.",
      "min": 1,
      "max": 240,
      "step": 1
    },
    { 
      "type": "text", 
      "defaultValue": imageGallery([
        {
          "src": "http://capypara.de/pebble/tg1.png",
          "label": "Background 1"
        },
        {
          "src": "http://capypara.de/pebble/tg2.png",
          "label": "Background 2"
        },
        {
          "src": "http://capypara.de/pebble/tg3.png",
          "label": "Background 3"
        }
      ])
    }
    ]
  }, 
  {
  "type": "section",
  "items": [
    {
      "type": "heading",
      "defaultValue": "Temperature"
    },
    {
      "type": "toggle",
      "messageKey": "CfgShowTemperature",
      "defaultValue": true,
      "label": "Show temperature",
      "description": "Displayed in the top left corner."
    },
    {
      "type": "select",
      "messageKey": "CfgTemperatureUnit",
      "defaultValue": 0,
      "label": "Temperature Unit",
      "options": [
        { 
          "label": "Fahrenheit",
          "value": 0
        },
        { 
          "label": "Celcius",
          "value": 1
        }
      ]
    }
    ]
  }, 
  {
  "type": "section",
  "items": [
    {
      "type": "heading",
      "defaultValue": "Date"
    },
    {
      "type": "toggle",
      "messageKey": "CfgShowDate",
      "label": "Show date",
      "defaultValue": true,
      "description": "Displayed in the top right corner."
    },
    {
      "type": "select",
      "messageKey": "CfgDateFormat",
      "defaultValue": 0,
      "label": "Date Format",
      "options": [
        { 
          "label": "Month/Day (MM/DD)",
          "value": 0
        },
        { 
          "label": "Day/Month (DD/MM)",
          "value": 1
        }
      ]
    }
    ]
  }, 
  {
  "type": "section",
  "items": [
    {
      "type": "heading",
      "defaultValue": "Step goal"
    },
    {
      "type": "toggle",
      "messageKey": "CfgShowSteps",
      "label": "Show step goal progress",
      "defaultValue": true,
      "description": "Displayed under the time."
    },
    {
      "type": "slider",
      "messageKey": "CfgStepGoal",
      "defaultValue": 5000,
      "label": "Step goal",
      "description": "Your step goal. A fully green bar means you reached your goal, a fully blue bar means, you doubled your goal.",
      "min": 1,
      "max": 10000,
      "step": 1
    }
    ]
  }, 
  {
  "type": "section",
  "items": [
    {
      "type": "heading",
      "defaultValue": "Bottom Textbox"
    },
    {
      "type": "select",
      "messageKey": "CfgBottomDisplay",
      "defaultValue": 1,
      "description": "What text should the bottom textbox display?",
      "options": [
        { 
          "label": "None (hide)",
          "value": 0
        },
        { 
          "label": "Weather",
          "value": 1
        }
      ]
    }
    ]
  }, 
  {
  "type": "section",
  "items": [
    {
      "type": "heading",
      "defaultValue": "Quick View Action"
    },
    {
      "type": "select",
      "messageKey": "CfgQuickView",
      "defaultValue": 0,//1,
      "description": "What should be done, if a Quick View message is displayed? More options will be added soon.",
      "options": [
        { 
          "label": "Nothing (QuickView will hide bottom textbox)",
          "value": 0
        }/*,
        { 
          "label": "Move Bottom Textbox Up (Cluttered)",
          "value": 1 
        }*/
      ]
    }/*,
    { 
      "type": "text", 
      "defaultValue": imageGallery([
        {
          "src": "http://parakoopa.de/pebble/test2.png",
          "label": "Nothing"
        },
        {
          "src": "http://parakoopa.de/pebble/test2.png",
          "label": "Move Bottom Up"
        }
      ])
    }*/
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save"
  },
  {
    "type": "text",
    "defaultValue": "Reload the watchface after you saved to apply all of the settings."
  }
];