using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Iteratoren
{
    class Translations : IEnumerable<string>
    {
        private List<string[]> dictionary = new List<string[]>();

        public void AddTranslation(string german, string english, string french) {
            dictionary.Add(new string[] { german, english, french});
        }

        public IEnumerable<string> GermanWords() {
            foreach (string[] wordSet in dictionary)
                yield return wordSet[0];
        }


        public IEnumerator<string> GetEnumerator()
        {
            foreach (string[] wordSet in dictionary)
                foreach (string word in wordSet)
                    yield return word;
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
    }
}
