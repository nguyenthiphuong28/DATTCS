using System;
using System.Collections.Generic;

namespace Lap6
{
    // Lớp trừu tượng
    internal abstract class Xemay
    {
        protected string bienso;
        protected int namdangky;

        // Khởi tạo không tham số
        protected Xemay()
        {
            bienso = "79-AA.12345";
            namdangky = 2025;
        }

        // Khởi tạo có tham số
        public Xemay(string bs, int nam)
        {
            bienso = bs;
            namdangky = nam;
        }

        // Nhập thông tin
        public virtual void Nhap()
        {
            Console.Write("Nhập biển số: ");
            bienso = Console.ReadLine();

            Console.Write("Nhập năm đăng ký: ");
            while (!int.TryParse(Console.ReadLine(), out namdangky))
            {
                Console.Write("Nhập lại năm đăng ký: ");
            }
        }

        // Phương thức trừu tượng để tính bảo hành
        public abstract int TinhBH();

        // Xuất thông tin
        public void Xuat()
        {
            Console.WriteLine($"Biển số: {bienso}, Năm đăng ký: {namdangky}, Hạn bảo hành đến năm: {TinhBH()}");
        }
    }

    // Lớp kế thừa Xe điện
    class Xedien : Xemay
    {
        float pin;

        public Xedien() : base()
        {
            pin = 12.7f;
        }

        public override void Nhap()
        {
            base.Nhap();
            Console.Write("Nhập dung lượng pin: ");
            while (!float.TryParse(Console.ReadLine(), out pin))
            {
                Console.Write("Nhập lại dung lượng pin: ");
            }
        }

        public override int TinhBH()
        {
            return namdangky + 3;
        }
    }

    // Lớp kế thừa Xe xăng
    class Xexang : Xemay
    {
        float dungtich;

        public Xexang() : base()
        {
            dungtich = 0.0f;
        }

        public override void Nhap()
        {
            base.Nhap();
            Console.Write("Nhập dung tích bình xăng: ");
            while (!float.TryParse(Console.ReadLine(), out dungtich))
            {
                Console.Write("Nhập lại dung tích bình xăng: ");
            }
        }

        public override int TinhBH()
        {
            return namdangky + 2;
        }
    }

    // Danh sách xe máy
    class DS_Xemay
    {
        List<Xemay> ds;

        public DS_Xemay()
        {
            ds = new List<Xemay>();
        }

        public void NhapDS()
        {
            int chon;
            do
            {
                Console.WriteLine("\n1. Thêm xe điện");
                Console.WriteLine("2. Thêm xe xăng");
                Console.WriteLine("0. Thoát");
                Console.Write("Chọn loại xe để thêm: ");
                while (!int.TryParse(Console.ReadLine(), out chon) || chon < 0 || chon > 2)
                {
                    Console.Write("Vui lòng chọn lại (0-2): ");
                }

                Xemay xm = null;
                switch (chon)
                {
                    case 1:
                        xm = new Xedien();
                        break;
                    case 2:
                        xm = new Xexang();
                        break;
                    case 0:
                        return;
                }

                xm.Nhap();
                ds.Add(xm);

            } while (true);
        }

        public void XuatDS()
        {
            Console.WriteLine("\n--- Danh sách xe máy ---");
            foreach (var xm in ds)
            {
                xm.Xuat();
            }
        }
    }
}
