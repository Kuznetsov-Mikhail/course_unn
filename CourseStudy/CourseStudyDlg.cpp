
// CourseStudyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "CourseStudy.h"
#include "CourseStudyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CCourseStudyDlg



CCourseStudyDlg::CCourseStudyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COURSESTUDY_DIALOG, pParent)
	, bitrate(5e6)
	, sampling(35e7)
	, bits_size(300)
	, delay_size(100)
	, delay_lama(0)
	, Signals_or_Spectrs(FALSE)
	, noize_lvl(10)
	, f_dop(3e4)
	, Dopler_On(TRUE)
	, scramble(TRUE)
	, Signals_generator_type(FALSE)
	, test_time_cr(0)
	, _k(32)
	, pi_on_edit(0)
	, win_size(70)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCourseStudyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SIGNAL1, viewer1);
	DDX_Control(pDX, IDC_SIGNAL2, viewer2);
	DDX_Control(pDX, IDC_SIGNAL3, viewer3);
	DDX_Text(pDX, IDC_EDIT3, bitrate);
	DDX_Text(pDX, IDC_EDIT4, sampling);
	DDX_Text(pDX, IDC_EDIT5, bits_size);
	DDX_Text(pDX, IDC_EDIT6, delay_size);
	DDX_Text(pDX, IDC_EDIT7, delay_lama);
	DDX_Check(pDX, IDC_CHECK4, Signals_or_Spectrs);
	DDX_Text(pDX, IDC_EDIT8, noize_lvl);
	DDX_Text(pDX, IDC_EDIT1, f_dop);
	DDX_Check(pDX, IDC_CHECK1, Dopler_On);
	DDX_Check(pDX, IDC_CHECK2, scramble);
	DDX_Check(pDX, IDC_CHECK3, Signals_generator_type);
	DDX_Text(pDX, IDC_EDIT11, test_time_cr);
	DDX_Text(pDX, IDC_EDIT2, _k);
	DDX_Text(pDX, IDC_EDIT9, pi_on_edit);
	DDX_Text(pDX, IDC_EDIT10, win_size);
}

BEGIN_MESSAGE_MAP(CCourseStudyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CCourseStudyDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CCourseStudyDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK4, &CCourseStudyDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_BUTTON3, &CCourseStudyDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCourseStudyDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CCourseStudyDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CCourseStudyDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCourseStudyDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCourseStudyDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCourseStudyDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// Обработчики сообщений CCourseStudyDlg

BOOL CCourseStudyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CCourseStudyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CCourseStudyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CCourseStudyDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}
DoubleArray CCourseStudyDlg::vectorToArray(std::vector<double>& v)
{
	return (v.size() == 0) ? DoubleArray() : DoubleArray(v.data(), (int)v.size());
}
void CCourseStudyDlg::ViewerDraw(vector<complex<double>>& data, int Xmax, CChartViewer& viewer_num)
{
	// In this example, we simply use random data for the 3 data series.
	vector<double> dataReal, dataImag;
	for (int i = 0; i < data.size(); i++)
	{
		dataReal.push_back(data[i].real());
		dataImag.push_back(data[i].imag());
	}
	DoubleArray Arr_dataReal = vectorToArray(dataReal);
	DoubleArray Arr_dataImag = vectorToArray(dataImag);
	vector<double>Datatime;
	for (int i = 0; i < Xmax; i++)Datatime.push_back(i);
	DoubleArray timeStamps = vectorToArray(Datatime);

	// Create a XYChart object of size 600 x 400 pixels
	XYChart* c = new XYChart(850, 240);

	// Add a title box using grey (0x555555) 20pt Arial font
	//c->addTitle("", "arial.ttf", 20, 0x555555);

	// Set the plotarea at (70, 70) and of size 500 x 300 pixels, with transparent background and
	// border and light grey (0xcccccc) horizontal grid lines
	c->setPlotArea(70, 50, 700, 120, Chart::Transparent, -1, Chart::Transparent, 0xcccccc);

	// Add a legend box with horizontal layout above the plot area at (70, 35). Use 12pt Arial font,
	// transparent background and border, and line style legend icon.
	LegendBox* b = c->addLegend(20, 5, false, "arial.ttf", 12);
	b->setBackground(Chart::Transparent, Chart::Transparent);
	b->setLineStyleKey();

	// Set axis label font to 12pt Arial
	c->xAxis()->setLabelStyle("arial.ttf", 12);
	c->yAxis()->setLabelStyle("arial.ttf", 12);

	// Set the x and y axis stems to transparent, and the x-axis tick color to grey (0xaaaaaa)
	c->xAxis()->setColors(Chart::TextColor, Chart::TextColor, Chart::TextColor, 0xaaaaaa);
	c->yAxis()->setColors(Chart::TextColor);

	// Set the major/minor tick lengths for the x-axis to 10 and 0.
	c->xAxis()->setTickLength(10, 0);

	// For the automatic axis labels, set the minimum spacing to 80/40 pixels for the x/y axis.
	c->xAxis()->setTickDensity(80);
	c->yAxis()->setTickDensity(40);

	// Add a title to the y axis using dark grey (0x555555) 14pt Arial font
	c->yAxis()->setTitle("", "arial.ttf", 14, 0x555555);

	// Add a line layer to the chart with 3-pixel line width
	LineLayer* layer = c->addLineLayer();
	layer->setLineWidth(3);

	// Add 3 data series to the line layer
	layer->addDataSet(Arr_dataReal, 0x5588cc, "Real");
	layer->addDataSet(Arr_dataImag, 0xee9944, "Imag");
	// The x-coordinates for the line layer
	layer->setXData(timeStamps);
	viewer_num.setChart(c);
	delete c;
}
void CCourseStudyDlg::ViewerDrawSpectrum(vector<double>& data, int Xmax, CChartViewer& viewer_num)
{
	// In this example, we simply use random data for the 3 data series.
	DoubleArray Arr_dataReal = vectorToArray(data);
	vector<double>Datatime;
	double step = sampling / data.size();
	for (int i = 0; i < Xmax; i++)Datatime.push_back(i * step);
	DoubleArray timeStamps = vectorToArray(Datatime);

	// Create a XYChart object of size 600 x 400 pixels
	XYChart* c = new XYChart(850, 240);

	// Add a title box using grey (0x555555) 20pt Arial font
	//c->addTitle("", "arial.ttf", 20, 0x555555);

	// Set the plotarea at (70, 70) and of size 500 x 300 pixels, with transparent background and
	// border and light grey (0xcccccc) horizontal grid lines
	c->setPlotArea(70, 50, 700, 120, Chart::Transparent, -1, Chart::Transparent, 0xcccccc);

	// Add a legend box with horizontal layout above the plot area at (70, 35). Use 12pt Arial font,
	// transparent background and border, and line style legend icon.
	LegendBox* b = c->addLegend(20, 5, false, "arial.ttf", 12);
	b->setBackground(Chart::Transparent, Chart::Transparent);
	b->setLineStyleKey();

	// Set axis label font to 12pt Arial
	c->xAxis()->setLabelStyle("arial.ttf", 12);
	c->yAxis()->setLabelStyle("arial.ttf", 12);

	// Set the x and y axis stems to transparent, and the x-axis tick color to grey (0xaaaaaa)
	c->xAxis()->setColors(Chart::TextColor, Chart::TextColor, Chart::TextColor, 0xaaaaaa);
	c->yAxis()->setColors(Chart::TextColor);

	// Set the major/minor tick lengths for the x-axis to 10 and 0.
	c->xAxis()->setTickLength(10, 0);

	// For the automatic axis labels, set the minimum spacing to 80/40 pixels for the x/y axis.
	c->xAxis()->setTickDensity(80);
	c->yAxis()->setTickDensity(40);

	// Add a title to the y axis using dark grey (0x555555) 14pt Arial font
	c->yAxis()->setTitle("", "arial.ttf", 14, 0x555555);

	// Add a line layer to the chart with 3-pixel line width
	LineLayer* layer = c->addLineLayer();
	layer->setLineWidth(3);

	// Add 3 data series to the line layer
	layer->addDataSet(Arr_dataReal, 0x5588cc, "Real");
	// The x-coordinates for the line layer
	layer->setXData(timeStamps);
	viewer_num.setChart(c);
	delete c;
}
void CCourseStudyDlg::ViewerDraw(vector<double>& data, int Xmax, CChartViewer& viewer_num)
{
	// In this example, we simply use random data for the 3 data series.
	DoubleArray Arr_dataReal = vectorToArray(data);
	vector<double>Datatime;
	int bits = 1;
	double step = 1;
	if (data.size() != 0)
	{
		bits = data.size() / sp.bit_time;
		step = (double)bits / data.size();
	}
	for (int i = 0; i < Xmax; i++)Datatime.push_back(i * step);
	DoubleArray timeStamps = vectorToArray(Datatime);

	// Create a XYChart object of size 600 x 400 pixels
	XYChart* c = new XYChart(850, 240);

	// Add a title box using grey (0x555555) 20pt Arial font
	//c->addTitle("", "arial.ttf", 20, 0x555555);

	// Set the plotarea at (70, 70) and of size 500 x 300 pixels, with transparent background and
	// border and light grey (0xcccccc) horizontal grid lines
	c->setPlotArea(70, 50, 700, 120, Chart::Transparent, -1, Chart::Transparent, 0xcccccc);

	// Add a legend box with horizontal layout above the plot area at (70, 35). Use 12pt Arial font,
	// transparent background and border, and line style legend icon.
	LegendBox* b = c->addLegend(20, 5, false, "arial.ttf", 12);
	b->setBackground(Chart::Transparent, Chart::Transparent);
	b->setLineStyleKey();

	// Set axis label font to 12pt Arial
	c->xAxis()->setLabelStyle("arial.ttf", 12);
	c->yAxis()->setLabelStyle("arial.ttf", 12);

	// Set the x and y axis stems to transparent, and the x-axis tick color to grey (0xaaaaaa)
	c->xAxis()->setColors(Chart::TextColor, Chart::TextColor, Chart::TextColor, 0xaaaaaa);
	c->yAxis()->setColors(Chart::TextColor);

	// Set the major/minor tick lengths for the x-axis to 10 and 0.
	c->xAxis()->setTickLength(10, 0);

	// For the automatic axis labels, set the minimum spacing to 80/40 pixels for the x/y axis.
	c->xAxis()->setTickDensity(80);
	c->yAxis()->setTickDensity(40);

	// Add a title to the y axis using dark grey (0x555555) 14pt Arial font
	c->yAxis()->setTitle("", "arial.ttf", 14, 0x555555);

	// Add a line layer to the chart with 3-pixel line width
	LineLayer* layer = c->addLineLayer();
	layer->setLineWidth(3);

	// Add 3 data series to the line layer
	layer->addDataSet(Arr_dataReal, 0x5588cc, "Real");
	// The x-coordinates for the line layer
	layer->setXData(timeStamps);
	viewer_num.setChart(c);
	delete c;
}
void CCourseStudyDlg::ViewerDraw(vector<vector<double>>& data, double Xmin, double Xmax, CChartViewer& viewer_num, string PathPic)
{
	if (data.empty())return;
	// In this example, we simply use random data for the 3 data series.
	vector<DoubleArray> Arr_dataReal; Arr_dataReal.resize(data.size());
	for (int i = 0; i < data.size(); i++)
	{
		Arr_dataReal[i] = vectorToArray(data[i]);
	}

	vector<double>Datatime;

	double OXstep = (Xmax - Xmin) / (data[0].size() - 1);
	for (double i = Xmin; i <= Xmax; i += OXstep)Datatime.push_back(i);
	DoubleArray timeStamps = vectorToArray(Datatime);

	// Create a XYChart object of size 600 x 400 pixels
	XYChart* c = new XYChart(850, 240);

	// Add a title box using grey (0x555555) 20pt Arial font
	//c->addTitle("", "arial.ttf", 20, 0x555555);

	// Set the plotarea at (70, 70) and of size 500 x 300 pixels, with transparent background and
	// border and light grey (0xcccccc) horizontal grid lines
	c->setPlotArea(70, 50, 700, 120, Chart::Transparent, -1, Chart::Transparent, 0xcccccc);

	// Add a legend box with horizontal layout above the plot area at (70, 35). Use 12pt Arial font,
	// transparent background and border, and line style legend icon.
	LegendBox* b = c->addLegend(20, 5, false, "arial.ttf", 12);
	b->setBackground(Chart::Transparent, Chart::Transparent);
	b->setLineStyleKey();

	// Set axis label font to 12pt Arial
	c->xAxis()->setLabelStyle("arial.ttf", 12);
	c->yAxis()->setLabelStyle("arial.ttf", 12);

	// Set the x and y axis stems to transparent, and the x-axis tick color to grey (0xaaaaaa)
	c->xAxis()->setColors(Chart::TextColor, Chart::TextColor, Chart::TextColor, 0xaaaaaa);
	c->yAxis()->setColors(Chart::TextColor);

	// Set the major/minor tick lengths for the x-axis to 10 and 0.
	c->xAxis()->setTickLength(10, 0);

	// For the automatic axis labels, set the minimum spacing to 80/40 pixels for the x/y axis.
	c->xAxis()->setTickDensity(80);
	c->yAxis()->setTickDensity(40);

	// Add a title to the y axis using dark grey (0x555555) 14pt Arial font
	c->yAxis()->setTitle("", "arial.ttf", 14, 0x555555);

	// Add a line layer to the chart with 3-pixel line width
	LineLayer* layer = c->addLineLayer();
	layer->setLineWidth(3);
	//
	layer->setDataLabelFormat("{value|1} ");
	// Add 3 data series to the line layer
	for (int i = 0; i < Arr_dataReal.size(); i++)
	{
		stringstream ss;
		ss << "Data " << i;
		string name = ss.str();
		int color = 0. + 16777216 * rand() / RAND_MAX;
		layer->addDataSet(Arr_dataReal[i], color, name.c_str());
	}
	// The x-coordinates for the line layer
	layer->setXData(timeStamps);
	viewer_num.setChart(c);
	const char* chPathPic = PathPic.c_str();
	c->makeChart(chPathPic);
	delete c;
}
//VIcourse
void CCourseStudyDlg::TrueViewerDraw(vector<vector<double>>& data, double Xmin, double Xmax, CChartViewer& viewer_num, string PathPic, bool podpisi)
{
	if (data.empty())return;
	// In this example, we simply use random data for the 3 data series.
	vector<DoubleArray> Arr_dataReal; Arr_dataReal.resize(data.size());
	for (int i = 0; i < data.size(); i++)
	{
		Arr_dataReal[i] = vectorToArray(data[i]);
	}

	vector<double>Datatime;

	double OXstep = (Xmax - Xmin) / (data[0].size() - 1);
	for (double i = Xmin; i <= Xmax; i += OXstep)Datatime.push_back(i);
	DoubleArray timeStamps = vectorToArray(Datatime);

	// Create a XYChart object of size 600 x 400 pixels
	XYChart* c = new XYChart(850, 240);

	// Add a title box using grey (0x555555) 20pt Arial font
	//c->addTitle("", "arial.ttf", 20, 0x555555);

	// Set the plotarea at (70, 70) and of size 500 x 300 pixels, with transparent background and
	// border and light grey (0xcccccc) horizontal grid lines
	c->setPlotArea(70, 50, 700, 120, Chart::Transparent, -1, Chart::Transparent, 0xcccccc);

	// Add a legend box with horizontal layout above the plot area at (70, 35). Use 12pt Arial font,
	// transparent background and border, and line style legend icon.
	LegendBox* b = c->addLegend(20, 5, false, "arial.ttf", 12);
	b->setBackground(Chart::Transparent, Chart::Transparent);
	b->setLineStyleKey();

	// Set axis label font to 12pt Arial
	c->xAxis()->setLabelStyle("arial.ttf", 12);
	c->yAxis()->setLabelStyle("arial.ttf", 12);

	// Set the x and y axis stems to transparent, and the x-axis tick color to grey (0xaaaaaa)
	c->xAxis()->setColors(Chart::TextColor, Chart::TextColor, Chart::TextColor, 0xaaaaaa);
	c->yAxis()->setColors(Chart::TextColor);

	// Set the major/minor tick lengths for the x-axis to 10 and 0.
	c->xAxis()->setTickLength(10, 0);

	// For the automatic axis labels, set the minimum spacing to 80/40 pixels for the x/y axis.
	c->xAxis()->setTickDensity(80);
	c->yAxis()->setTickDensity(40);

	// Add a title to the y axis using dark grey (0x555555) 14pt Arial font
	c->yAxis()->setTitle("", "arial.ttf", 14, 0x555555);

	// Add a line layer to the chart with 3-pixel line width
	LineLayer* layer = c->addLineLayer();
	layer->setLineWidth(3);
	//
	if (podpisi) layer->setDataLabelFormat("{value|4} ");
	// Add 3 data series to the line layer
	for (int i = 0; i < Arr_dataReal.size(); i++)
	{
		stringstream ss;
		ss << "Data " << i;
		string name = ss.str();
		layer->addDataSet(Arr_dataReal[i], -1, name.c_str());
	}
	// The x-coordinates for the line layer
	layer->setXData(timeStamps);
	viewer_num.setChart(c);
	const char* chPathPic = PathPic.c_str();
	c->makeChart(chPathPic);
	delete c;
}
//Обновление переменных класса sp - класса обработки генерируемых сигналов
void CCourseStudyDlg::updateSP() //Обновление переменных класса sp - класса обработки генерируемых сигналов
{
	sp.BrV = bitrate;
	sp.sampling = sampling;
}

void CCourseStudyDlg::OnBnClickedCheck4()
{
	UpdateData(1);
	if (Signals_or_Spectrs)
	{
		vector <double> ImSpectr1Mod;
		vector <double> ImSpectr2Mod;
		for (int i = 0; i < ImSpectr1.size(); i++)
		{
			ImSpectr1Mod.push_back(sqrt(pow(ImSpectr1[i].real(), 2) + pow(ImSpectr1[i].real(), 2)));
		}
		for (int i = 0; i < ImSpectr2.size(); i++)
		{
			ImSpectr2Mod.push_back(sqrt(pow(ImSpectr2[i].real(), 2) + pow(ImSpectr2[i].real(), 2)));
		}
		ViewerDrawSpectrum(ImSpectr1Mod, ImSpectr1Mod.size(), viewer1);
		ViewerDrawSpectrum(ImSpectr2Mod, ImSpectr2Mod.size(), viewer2);
	}
	else
	{
		ViewerDraw(ImSignal1, ImSignal1.size(), viewer1);
		ViewerDraw(ImSignal2, ImSignal2.size(), viewer2);
	}
	UpdateData(0);
}
//Генерация сигналов
void CCourseStudyDlg::OnBnClickedButton1()
{
	UpdateData(1);
	SetCursor(LoadCursor(nullptr, IDC_WAIT));
	Signals_Gen(bits_size, delay_size, noize_lvl);
	OnBnClickedCheck4();
	SetCursor(LoadCursor(nullptr, IDC_ARROW));
	UpdateData(0);
}

void CCourseStudyDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	SetCursor(LoadCursor(nullptr, IDC_WAIT));
	updateSP();
	//////////////////// Создание фильтров
	sp.fir_s.clear();
	sp.fir_s.resize(sp.operating_frequencies.size());
	for (int i = 0; i < sp.operating_frequencies.size(); i++)
	{
		double freq1 = ((sp.operating_frequencies[i] - 912.5) * pow(10, 6) - (sp.BrV / 4));
		double freq2 = ((sp.operating_frequencies[i] - 912.5) * pow(10, 6) + (sp.BrV / 4));
		//double trans_zone = (sp.BrV / 8.) * (3./2.); /// ПОЧЕМУ!!!! НЕ РАБОТАЕТ ПРИ sp.BrV / 8.
		double trans_zone = (sp.BrV / 4.);
		CreateFirFilter(freq1, freq2, trans_zone, sampling, sp.fir_s[i]);
	}
	SetCursor(LoadCursor(nullptr, IDC_ARROW));
	UpdateData(FALSE);
}

void CCourseStudyDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	SetCursor(LoadCursor(nullptr, IDC_WAIT));
	updateSP();
	int found_delay;
	auto start = steady_clock::now();
	pi_on_edit = sp.Uncertainty_ipp_jtids(delay_size, ImSignal1, ImSignal2, _k, ResearchRrr, found_delay, delay_lama);
	auto end = steady_clock::now();
	auto elapsed = duration_cast<milliseconds>(end - start);
	test_time_cr = (double)elapsed.count()/1000.;
	sp.vec_normalize(ResearchRrr);
	ViewerDraw(ResearchRrr, ResearchRrr.size(), viewer3);
	SetCursor(LoadCursor(nullptr, IDC_ARROW));
	UpdateData(FALSE);
}


void CCourseStudyDlg::OnBnClickedButton4()
{
	UpdateData(TRUE);
	SetCursor(LoadCursor(nullptr, IDC_WAIT));
	updateSP();
	int found_delay;
	auto start = steady_clock::now();
	sp.pre_nonlinear_filtering(sp.sampling / 4, sp.sampling, sp.BrV, sp.AA_matr, win_size);
	pi_on_edit = sp.Correlation_omp_jtids_with_nl_filtering(delay_size, ImSignal1, ImSignal2, ResearchRrr, found_delay, delay_lama, win_size);
	auto end = steady_clock::now();
	auto elapsed = duration_cast<milliseconds>(end - start);
	test_time_cr = (double)elapsed.count() / 1000.;
	sp.vec_normalize(ResearchRrr);
	ViewerDraw(ResearchRrr, ResearchRrr.size(), viewer3);
	SetCursor(LoadCursor(nullptr, IDC_ARROW));
	UpdateData(FALSE);
}
void CCourseStudyDlg::OnBnClickedButton5()
{
	UpdateData(TRUE);
	SetCursor(LoadCursor(nullptr, IDC_WAIT));
	updateSP();

	vector<vector<double>> study; study.resize(1/*3*/);
	int win_size_min = 10;
	int win_size_max = 100;
	int win_size_step_r = 10;
	int try_size = 10;
	for (int i = win_size_min; i < win_size_max; i+= win_size_step_r)
	{
		sp.pre_nonlinear_filtering(sp.sampling / 4, sp.sampling, sp.BrV, sp.AA_matr, i);
		double pi = 0;
		for (int j = 0; j < try_size; j++)
		{
			Signals_Gen(bits_size, delay_size, noize_lvl);
			int found_delay;
			pi += sp.Correlation_omp_jtids_with_nl_filtering(delay_size, ImSignal1, ImSignal2, ResearchRrr, found_delay, delay_lama, i);

		}
		pi /= try_size;
		study[0].push_back(pi);
	}
	TrueViewerDraw(study, win_size_min, win_size_max, viewer3, "win_size_study.png", true);
	SetCursor(LoadCursor(nullptr, IDC_ARROW));
	UpdateData(0);
}


void CCourseStudyDlg::OnBnClickedButton6() //snr study
{
	UpdateData(TRUE);
	updateSP();
	OnBnClickedButton2();
	SetCursor(LoadCursor(nullptr, IDC_WAIT));
	vector<vector<double>> study; study.resize(2);
	int noize_size_min = -15;
	int noize_size_max = -5;
	int noize_size_step_r = 2;
	int try_size = 10;
	sp.pre_nonlinear_filtering(sp.sampling / 4, sp.sampling, sp.BrV, sp.AA_matr, win_size);
	for (int i = noize_size_min; i <= noize_size_max; i += noize_size_step_r)
	{
		double pi1 = 0;
		double pi2 = 0;
		for (int j = 0; j < try_size; j++)
		{
			Signals_Gen(bits_size, delay_size, i);
			int found_delay;
			pi1 += sp.Uncertainty_ipp_jtids(i, ImSignal1, ImSignal2, _k, ResearchRrr, found_delay, delay_lama);
			pi2 += sp.Correlation_omp_jtids_with_nl_filtering(i, ImSignal1, ImSignal2, ResearchRrr, found_delay, delay_lama, win_size);
		}
		pi1 /= try_size;
		pi2 /= try_size;
		study[0].push_back(pi1);
		study[1].push_back(pi2);
	}
	TrueViewerDraw(study, noize_size_min, noize_size_max, viewer3, "snr_study.png", true);
	SetCursor(LoadCursor(nullptr, IDC_ARROW));
	UpdateData(0);
}


void CCourseStudyDlg::OnBnClickedButton7() //bits study
{
	UpdateData(TRUE);
	updateSP();
	OnBnClickedButton2();
	SetCursor(LoadCursor(nullptr, IDC_WAIT));
	vector<vector<double>> study; study.resize(2);
	int bits_size_min = 20;
	int bits_size_max = 130;
	int bits_size_step_r = 20;
	int try_size = 10;
	int minOx, maxOx;
	sp.pre_nonlinear_filtering(sp.sampling / 4, sp.sampling, sp.BrV, sp.AA_matr, win_size);
	for (int i = bits_size_min; i <= bits_size_max; i += bits_size_step_r)
	{
		double pi1 = 0;
		double pi2 = 0;
		for (int j = 0; j < try_size; j++)
		{
			Signals_Gen(i*4, i, noize_lvl);
			if (i == bits_size_min)minOx = ImSignal2.size();
			else maxOx = ImSignal2.size();
			int found_delay;
			pi1 += sp.Uncertainty_ipp_jtids(i, ImSignal1, ImSignal2, _k, ResearchRrr, found_delay, delay_lama);
			pi2 += sp.Correlation_omp_jtids_with_nl_filtering(i, ImSignal1, ImSignal2, ResearchRrr, found_delay, delay_lama, win_size);
		}
		pi1 /= try_size;
		pi2 /= try_size;
		study[0].push_back(pi1);
		study[1].push_back(pi2);
	}
	TrueViewerDraw(study, minOx, maxOx, viewer3, "bits_study.png", true);
	SetCursor(LoadCursor(nullptr, IDC_ARROW));
	UpdateData(0);
}


void CCourseStudyDlg::OnBnClickedButton8() //speed
{
	UpdateData(TRUE);
	updateSP();
	OnBnClickedButton2();
	SetCursor(LoadCursor(nullptr, IDC_WAIT));
	vector<vector<double>> study; study.resize(2);
	int bits_size_min = 30;
	int bits_size_max = 130;
	int bits_size_step_r = 20;
	int try_size = 1;
	int minOx, maxOx;
	sp.pre_nonlinear_filtering(sp.sampling / 4, sp.sampling, sp.BrV, sp.AA_matr, win_size);
	for (int i = bits_size_min; i <= bits_size_max; i += bits_size_step_r)
	{
		double time_1 = 0;
		double time_2 = 0;
		for (int j = 0; j < try_size; j++)
		{
			Signals_Gen(i*4, i, noize_lvl);
			if (i == bits_size_min)minOx = ImSignal2.size();
			else maxOx = ImSignal2.size();
			int found_delay;
			auto start1 = steady_clock::now();
			pi_on_edit = sp.Uncertainty_ipp_jtids(i, ImSignal1, ImSignal2, _k, ResearchRrr, found_delay, delay_lama);
			auto end1 = steady_clock::now();
			auto elapsed1 = duration_cast<milliseconds>(end1 - start1);
			time_1 += (double)elapsed1.count() / 1000.;

			auto start2 = steady_clock::now();
			pi_on_edit = sp.Correlation_omp_jtids_with_nl_filtering(i, ImSignal1, ImSignal2, ResearchRrr, found_delay, delay_lama, win_size);
			auto end2 = steady_clock::now();
			auto elapsed2 = duration_cast<milliseconds>(end2 - start2);
			time_2 += (double)elapsed2.count() / 1000.;
		}
		time_1 /= try_size;
		time_2 /= try_size;
		study[0].push_back(time_1);
		study[1].push_back(time_2);
	}
	TrueViewerDraw(study, minOx, maxOx, viewer3, "speed_study.png", true);
	SetCursor(LoadCursor(nullptr, IDC_ARROW));
	UpdateData(0);
}
