using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lap6
{
    // Interface tên đúng quy ước C#
    interface IMuaVeThang
    {
        float TinhTienGiam();
    }

    // Lớp vé xe bus cơ bản
    class VexeBus
    {
        public int Tuyenthu { get; set; }
        public string DoiTuong { get; set; }
        public static readonly float GiaSan = 5000;

        public virtual void Nhap()
        {
            Console.Write("Nhập tuyến xe (số): ");
            int tuyen; // Declare 'tuyen' before using it
            while (!int.TryParse(Console.ReadLine(), out tuyen) || tuyen <= 0)
                Console.Write("Nhập lại tuyến xe (số > 0): ");
            Tuyenthu = tuyen;

            Console.Write("Nhập đối tượng (học sinh, sinh viên, thương binh...): ");
            DoiTuong = Console.ReadLine();
        }


        public virtual void Xuat()
        {
            Console.WriteLine($"Tuyến: {Tuyenthu}, Đối tượng: {DoiTuong}, Giá vé: {TinhGiaVe()}");
        }

        public virtual float TinhGiaVe()
        {
            if (DoiTuong.ToLower().Contains("học sinh") || DoiTuong.ToLower().Contains("sinh viên"))
                return GiaSan;
            else
                return GiaSan * 1.2f;
        }
    }

    // Lớp vé xe bus liên huyện kế thừa và thực hiện interface
    class VexeBusLienHuyen : VexeBus, IMuaVeThang
    {
        public int SoThang { get; set; }
        public float ChieuDai { get; set; } // km

        public override void Nhap()
        {
            base.Nhap();
            Console.Write("Nhập chiều dài tuyến (km): ");
            float cd; // Declare 'cd' before using it
            while (!float.TryParse(Console.ReadLine(), out cd) || cd < 0)
                Console.Write("Nhập lại chiều dài hợp lệ: ");
            ChieuDai = cd;

            Console.Write("Nhập số tháng mua vé: ");
            int thang; // Declare 'thang' before using it
            while (!int.TryParse(Console.ReadLine(), out thang) || thang <= 0)
                Console.Write("Nhập lại số tháng > 0: ");
            SoThang = thang;
        }


        public override void Xuat()
        {
            Console.WriteLine($"Tuyến: {Tuyenthu}, Đối tượng: {DoiTuong}, Chiều dài: {ChieuDai} km, Số tháng: {SoThang}, Giá vé sau giảm: {TinhGiaVe()}");
        }

        public override float TinhGiaVe()
        {
            float giaGoc = base.TinhGiaVe();
            return giaGoc - TinhTienGiam();
        }

        public float TinhTienGiam()
        {
            float giaGoc = base.TinhGiaVe();
            if (SoThang >= 3 && ChieuDai >= 20)
                return giaGoc * 0.15f;
            else
                return giaGoc * 0.10f;
        }
    }
}
