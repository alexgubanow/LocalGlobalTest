using mechLIB;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace testQuatern
{
    class Program
    {
        static void Main(string[] args)
        {
            double iter = 1E7;
            Vector3 globVq = new Vector3();
            Vector3 gFn = new Vector3();
            Vector3 rV = new Vector3() { X = 75.22f, Y = 25.09f };
            Vector3 rLocV = new Vector3() { X = 1 };
            Vector3 radiusPoint = new Vector3() { X = -4.4871f, Y = 13.4166f }; 
            for (int i = 0; i < 5; i++)
            {
                CalcDCM(rV, radiusPoint, i / 1E3f, ref gFn);
                CalcQTR(rV, rLocV, i / 1E3f, ref globVq);
            }
            for (int k = 1; k < 4; k++)
            {
                var sw = System.Diagnostics.Stopwatch.StartNew();
                for (int i = 0; i < iter; i++)
                {
                    CalcDCM(rV, radiusPoint, i / 1E3f, ref gFn);

                }
                sw.Stop();
                Console.WriteLine("{0} dcm: {1} ms", k, sw.Elapsed.TotalMilliseconds);

                sw = System.Diagnostics.Stopwatch.StartNew();
                for (int i = 0; i < iter; i++)
                {
                    CalcQTR(rV, rLocV, i / 1E3f, ref globVq);
                }
                sw.Stop();
                Console.WriteLine("{0} qtr: {1} ms", k, sw.Elapsed.TotalMilliseconds);
            }
            Console.WriteLine("gFn.x: {0}", gFn.X);
            Console.WriteLine("globVq.x: {0}", globVq.X);
            Console.WriteLine("Press any key to exit...");
            Console.Read();
        }
        private static void CalcDCM(Vector3 rV, Vector3 radiusPoint, float a, ref Vector3 gFn)
        {
            dcm_t dcm = new dcm_t(rV, radiusPoint);
            Vector3 lv = new Vector3() { X = 63.59f + a };
            dcm.ToGlob(lv, ref gFn);

            //Vector3 gv = new Vector3() { X = 60.3228f, Y = 20.1210f };
            //Vector3 lBpUx = new Vector3();
            //dcm.ToLoc(gv, ref lBpUx);
        }
        private static void CalcQTR(Vector3 rV, Vector3 rLocV, float a, ref Vector3 globVq )
        {
            rV = Vector3.Normalize(rV);
            float halfCosAngle = 0.5f * Vector3.Dot(rV, rLocV);
            Quaternion q = new Quaternion(Math.Sqrt(0.5f + halfCosAngle).ToFloat(), Math.Sqrt(0.5f - halfCosAngle).ToFloat(), 0, 0);



            //float cosXa = rV.X / rV.Length();
            //Quaternion q = new Quaternion(Math.Cos(Math.Acos(cosXa) / 2).ToFloat(), Math.Sin(Math.Acos(cosXa) / 2).ToFloat(), 0, 0);
            Vector3 lv = new Vector3() { X = 63.59f + a };
            globVq = Vector3.Transform(lv, q);

            //Quaternion qr = Quaternion.Negate(q);
            //Vector3 gv = new Vector3() { X = 60.3228f, Y = 20.1210f };
            //Vector3 locVq = Vector3.Transform(globVq, qr);
        }

    }
    public static class MathExtensions
    {
        public static float ToFloat(this double value) => (float)value;
    }
}
