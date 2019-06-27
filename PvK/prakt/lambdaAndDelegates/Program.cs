using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lambdaAndDelegates
{
    class Program
    {
        delegate bool intSelector(int x);
        delegate bool selector<T>(T x);
        static bool selectEvenNumbers(int x)
        {
            return x % 2 == 0;
        }
        static bool selectNumberLarger5(int x)
        {
            return x > 5;
        }
        static void ExtractFromIntArray(ref int[] arr, intSelector sel)
        {
            int[] newArr = new int[arr.Length];
            int counter = 0;
            for (int i = 0; i < arr.Length; i++)
            {
                if (sel(arr[i]))
                {
                    newArr[counter] = arr[i];
                    counter++;
                }
            }
            Array.Resize(ref newArr, counter);
            arr = newArr;
        }
        static void ExtractFromArray<T>(ref T[] arr, selector<T> sel) 
        {
            T []newArr = new T[arr.Length];
            int counter = 0;
            for (int i = 0; i < arr.Length; i++)
            {
                if (sel(arr[i]))
                {
                    newArr[counter] = arr[i];
                    counter++;
                }
            }
            Array.Resize(ref newArr, counter);
            arr = newArr;
        }
        static void ExtractFromArrayV<T>(ref T[] arr, Func<T,bool> sel)
        {
            T[] newArr = new T[arr.Length];
            int counter = 0;
            for (int i = 0; i < arr.Length; i++)
            {
                if (sel(arr[i]))
                {
                    newArr[counter] = arr[i];
                    counter++;
                }
            }
            Array.Resize(ref newArr, counter);
            arr = newArr;
        }

        static void Main(string[] args)
        {
            doubleMethod();

            Console.ReadKey();
        }

        static void doubleMethod() {
            Random rand = new Random();
            double[] dArr = new double[25];
            for (int i = 0; i < dArr.Length; i++)
            {
                dArr[i] = rand.NextDouble();
            }

            for (int i = 0; i < dArr.Length; i++)
            {
                Console.Write(dArr[i]);
            }

            Console.WriteLine("\n-- -- --");

            ExtractFromArrayV(ref dArr, x => (x*100)%10<5);

            for (int i = 0; i < dArr.Length; i++)
            {
                Console.Write(dArr[i]);
            }
        }

        static void intArrayMethod() {
            Random rand = new Random();
            int[] intArr = new int[25];
            for (int i = 0; i < intArr.Length; i++)
            {
                intArr[i] = rand.Next(0, 10);
            }

            for (int i = 0; i < intArr.Length; i++)
            {
                Console.Write(intArr[i]);
            }

            Console.WriteLine("\n-- -- --");

            // lambda for ExtractFromIntArray(ref intArr, selectNumberLarger5);
            // ExtractFromIntArray(ref intArr, x => x>5);            

            // lambda for ExtractFromIntArray(ref intArr, selectEvenNumbers);
            ExtractFromArrayV(ref intArr, x => x % 2 == 0);

            for (int i = 0; i < intArr.Length; i++)
            {
                Console.Write(intArr[i]);
            }
        }
    }
}
