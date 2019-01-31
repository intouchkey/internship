import json
import xmltodict
 
def convert(xml_file, xml_attribs=True):
    with open(xml_file, "rb") as f:    # notice the "rb" mode
        d = xmltodict.parse(f, xml_attribs=xml_attribs)
        return json.dumps(d, indent=4)

file_name = input("Please enter the file name (ex. weather.xml): ")

try:
    d = convert(file_name)
    with open("weather.json", 'w') as outfile:
        json.dump(d, outfile)
    print("Converted successfully!")
except:
    print("File not found")
