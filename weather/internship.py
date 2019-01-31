import json
import xmltodict
 
def convert(xml_file, xml_attribs=True):
    with open(xml_file, "rb") as f:    # notice the "rb" mode
        d = xmltodict.parse(f, xml_attribs=xml_attribs)
        return json.dumps(d, indent=4)

d = convert("weather.xml")
with open("weather.json", 'w') as outfile:
    json.dump(d, outfile)
