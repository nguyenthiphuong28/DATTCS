using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lap6
{
    internal class Program
    {

        static void Bai6_1()
        {
            Xemay xeDien = new Xedien();
            Console.WriteLine("Nhap thong tin xe dien:");
            xeDien.Nhap();
            xeDien.Xuat();

            // Tạo và nhập thông tin cho một xe xăng
            Xemay xeXang = new Xexang();
            Console.WriteLine("Nhap thong tin xe xang:");
            xeXang.Nhap();
            xeXang.Xuat();

            Console.WriteLine("Nhan phim bat ky de ket thuc....");
        }
        static void Bai6_2()
        {
            VexeBusLienHuyen ve = new VexeBusLienHuyen();
            ve.Nhap();
            ve.Xuat();

            Console.WriteLine("\nNhấn phím bất kỳ để thoát...");
        }
        static void Bai6_3()
        {
            List<Rectangle> danhSach = new List<Rectangle>();

            Console.Write("Nhập số lượng hình chữ nhật (2 <= n <= 10): ");
            int n;
            while (!int.TryParse(Console.ReadLine(), out n) || n < 2 || n > 10)
                Console.Write("Nhập lại số lượng hình hợp lệ: ");

            for (int i = 0; i < n; i++)
            {
                Console.WriteLine($"\nNhập hình thứ {i + 1}:");
                Rectangle r = new Rectangle();
                r.Nhap();
                danhSach.Add(r);
            }

            // Sắp xếp giảm dần theo chi phí vẽ
            danhSach.Sort();

            Console.WriteLine("\n--- Danh sách hình sau khi sắp xếp giảm dần theo chi phí vẽ:");
            foreach (var r in danhSach)
                r.Xuat();

            // Xóa hình đầu tiên có diện tích nhỏ hơn x
            Console.Write("\nNhập giá trị x để xóa hình có diện tích < x: ");
            float x;
            while (!float.TryParse(Console.ReadLine(), out x) || x < 0)
                Console.Write("Nhập lại x >= 0: ");
            int indexToRemove = danhSach.FindIndex(r => r.TinhDienTich() < x);
            if (indexToRemove >= 0)
            {
                danhSach.RemoveAt(indexToRemove);
                Console.WriteLine("Đã xóa hình có diện tích nhỏ hơn x.");
            }
            else
            {
                Console.WriteLine("Không có hình nào có diện tích nhỏ hơn x.");
            }

            // Thêm 1 hình vào vị trí i
            Console.Write("\nNhập vị trí i để thêm hình mới (0 <= i <= " + danhSach.Count + "): ");
            int iInsert;
            while (!int.TryParse(Console.ReadLine(), out iInsert) || iInsert < 0 || iInsert > danhSach.Count)
                Console.Write("Nhập lại i hợp lệ: ");
            Rectangle newRect = new Rectangle();
            Console.WriteLine("Nhập thông tin hình cần chèn:");
            newRect.Nhap();
            danhSach.Insert(iInsert, newRect);

            // Xuất danh sách sau khi thêm
            Console.WriteLine("\n--- Danh sách sau khi chèn hình:");
            foreach (var r in danhSach)
                r.Xuat();

            // Tính tổng chi phí vẽ
            float tongChiPhi = 0;
            foreach (var r in danhSach)
                tongChiPhi += r.TinhChiPhiVe();

            Console.WriteLine($"\nTổng chi phí vẽ của {danhSach.Count} hình là: {tongChiPhi:F2}");

            Console.WriteLine("\nNhấn phím bất kỳ để thoát...");
        }
        static void Bai6_4()
        {
            Console.WriteLine("Chọn loại máy tính (1: Laptop, 2: Macbook): ");
            int choice;
            while (!int.TryParse(Console.ReadLine(), out choice) || (choice != 1 && choice != 2))
                Console.WriteLine("Nhập lại lựa chọn hợp lệ (1 hoặc 2): ");

            MayTinh mt;
            if (choice == 1)
            {
                mt = new Laptop();
            }
            else
            {
                mt = new Macbook();
            }

            mt.Nhap();
        }
        static void Main(string[] args)
        {
            Bai6_1();
            Console.ReadKey();
            Bai6_2();
            Console.ReadKey();
            Bai6_3();
            Console.ReadKey();
            Bai6_4();
            Console.ReadKey();
        }
    }
}
