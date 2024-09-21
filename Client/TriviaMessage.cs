using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Windows.Controls;

namespace WpfApp1
{
    public class TriviaMessage
    {
        private string content;

        public TriviaMessage()
        {
            Code = default;
            Length = default;
            content = default;
        }
        public TriviaMessage(string message) // split joined message
        {
            if (message != null)
            {
                Code = (int)(message[0]);
                Length = message.Substring(1, 4);
                content = message.Substring(5);
            }
        }

        public TriviaMessage(int code, string content)
        {
            Code = code;
            Content = content;
        }

        // Message code [CODE][length][content]
        public int Code { get; set; }

        // Content length [code][LENGTH][content]
        public string Length { get; private set; }

        // Content itself [code][length][CONTENT]
        public string Content
        {
            get => content;
            set
            {
                content = value;
                Length = ByteArrayToHexString(BitConverter.GetBytes(content.Length).Reverse().ToArray());
            }
        }

        // joins all message information into one string, which ready to be sent
        public override string ToString()
        {
            return Code.ToString("X") + Length + content;
        }

        // parses the json serialized content into deserialized dictionary
        public Dictionary<string, string> ToDict()
        {
            return JsonConvert.DeserializeObject<Dictionary<string, string>>(content);
        }

        public Dictionary<string, object> ToMultiDict()
        {
            content = content.Trim('\0');
            return JsonConvert.DeserializeObject<Dictionary<string, object>>(content);
        }

        // Converts array of bytes into one hexa string
        public static string ByteArrayToHexString(byte[] ba)
        {
            StringBuilder hex = new StringBuilder(ba.Length * 2); // Multiply by 2 - hex is two chars
            foreach (byte b in ba)
                hex.AppendFormat("{0:x2}", b);
            return hex.ToString();
        }
    }
}