module.exports = [
  { 
    "type": "heading", 
    "defaultValue": "Example Header Item" 
  }, 
  { 
    "type": "text", 
    "defaultValue": "Example text item." 
  },
  {
  "type": "section",
  "items": [
    {
      "type": "heading",
      "defaultValue": "This is a section"
    },
    {
      "type": "input",
      "messageKey": "email",
      "label": "Email Address"
    },
    {
      "type": "toggle",
      "messageKey": "enableAnimations",
      "label": "Enable Animations"
    },
    {
      "type": "select",
      "messageKey": "flavor",
      "defaultValue": "grape",
      "label": "Favorite Flavor",
      "options": [
        { 
          "label": "", 
          "value": "" 
        },
        { 
          "label": "Berry",
          "value": "berry" 
        },
        { 
          "label": "Grape",
          "value": "grape" 
        },
        { 
          "label": "Banana",
          "value": "banana" 
        }
      ]
    },
    {
      "type": "color",
      "messageKey": "background",
      "label": "Background Color"
    },
    {
      "type": "button",
      "primary": true,
      "defaultValue": "Send"
    },
    {
      "type": "slider",
      "messageKey": "slider",
      "defaultValue": 15,
      "label": "Slider",
      "description": "This is the description for the slider",
      "min": 10,
      "max": 20,
      "step": 0.25
    },
    {
      "type": "submit",
      "defaultValue": "Save"
    }
  ]
}
];