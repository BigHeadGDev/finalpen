// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <microsoft.ui.xaml.window.h>
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

struct winrt::Windows::UI::Color myCol = winrt::Microsoft::UI::Colors::Green();


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::finalpen::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        auto windowNative{ this->try_as<::IWindowNative>() };
        HWND hWnd{ 0 };
        windowNative->get_WindowHandle(&hWnd);
        SetWindowPos(hWnd, NULL, 200, 200, 970, 630, NULL);
        this->Title(L"그림판 저장 실습");
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    
}

void winrt::finalpen::implementation::MainWindow::ColorPicker_ColorChanged(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& sender, winrt::Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const& args)
{
    myCol = args.NewColor();
}

void winrt::finalpen::implementation::MainWindow::MenuFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    vx.clear();
    vy.clear();
    size.clear();
    col.clear();
}


void winrt::finalpen::implementation::MainWindow::MenuFlyoutItem_Click_1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    FILE* fp;
    fopen_s(&fp, "C:/Users/goalk/Desktop/Cpractice/1.txt", "w");
    if (fp)
    {
        int n = vx.size();
        for (int i = 0; i < n; i++)
        {
            fprintf(fp, "%f %f %d %d %d %d %f ", vx[i], vy[i], col[i].R, col[i].G, col[i].B, col[i].A, size[i]);
        }
        fclose(fp);
    }
}


void winrt::finalpen::implementation::MainWindow::MenuFlyoutItem_Click_2(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    FILE* fp;
    fopen_s(&fp, "C:/Users/goalk/Desktop/Cpractice/1.txt", "r");
    if (fp)
    {
        vx.clear(); vy.clear(); size.clear(); col.clear();

        float x, y, s;
        int r, g, b, a;
        while (EOF != fscanf_s(fp, "%f %f %d %d %d %d %f", &x, &y, &r, &g, &b, &a, &s))
        {
            vx.push_back(x);
            vy.push_back(y);
            Windows::UI::Color tCol;
            tCol.R = r; tCol.G = g; tCol.B = b; tCol.A = a;
            col.push_back(tCol);
            size.push_back(s);
        }
        fclose(fp);
    }
}


void winrt::finalpen::implementation::MainWindow::MenuFlyoutItem_Click_3(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    this->Close();
}


void winrt::finalpen::implementation::MainWindow::Slider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
{
    mySize = e.NewValue();
}


void winrt::finalpen::implementation::MainWindow::myWrite_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    
}


void winrt::finalpen::implementation::MainWindow::myRead_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    
}


void winrt::finalpen::implementation::MainWindow::myClear_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    vx.clear();
    vy.clear();
    col.clear();
    size.clear();
    flag = false;
    px = 100;
    py = 100;
    mySize = 16;
}


void winrt::finalpen::implementation::MainWindow::CloseColor_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    ColorPicker().IsColorSpectrumVisible(false);
}


void winrt::finalpen::implementation::MainWindow::OpenColor_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    ColorPicker().IsColorSpectrumVisible(true);
}


void winrt::finalpen::implementation::MainWindow::CanvasControl_PointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    canvas.Invalidate();
}


void winrt::finalpen::implementation::MainWindow::CanvasControl_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    flag = true;
}


void winrt::finalpen::implementation::MainWindow::CanvasControl_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    flag = false;
    px = py = 0.0;
    vx.push_back(px);
    vy.push_back(py);
    col.push_back(myCol);
    size.push_back(mySize);
}


void winrt::finalpen::implementation::MainWindow::CanvasControl_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    px = e.GetCurrentPoint(canvas).Position().X;
    py = e.GetCurrentPoint(canvas).Position().Y;
    if (flag) {
        vx.push_back(px);
        vy.push_back(py);
        col.push_back(myCol);
        size.push_back(mySize);
        canvas.Invalidate();
    }
}


void winrt::finalpen::implementation::MainWindow::CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    int n = vx.size();
    if (n <= 2) return;
    for (int i = 1; i < n; i++) {
        if (vx[i] == 0.0 && vy[i] == 0.0) {
            i++; continue;
        }
        args.DrawingSession().DrawLine(vx[i - 1], vy[i - 1], vx[i], vy[i], col[i], size[i]);
        args.DrawingSession().FillCircle(vx[i - 1], vy[i - 1], size[i] / 2, col[i]);
        args.DrawingSession().FillCircle(vx[i], vy[i], size[i] / 2, col[i]);
    }
}





void winrt::finalpen::implementation::MainWindow::MenuFlyoutItem_Click_4(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    vx.clear();
    vy.clear();
    col.clear();
    size.clear();
    flag = false;
    px = 100;
    py = 100;
    mySize = 16;
}


void winrt::finalpen::implementation::MainWindow::MenuFlyoutItem_Click_5(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    ColorPicker().IsColorSpectrumVisible(false);
}


void winrt::finalpen::implementation::MainWindow::MenuFlyoutItem_Click_6(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    ColorPicker().IsColorSpectrumVisible(true);
}
