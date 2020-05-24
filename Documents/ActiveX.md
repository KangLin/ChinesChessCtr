## �й����� ActiveX �ؼ�

���ߣ� ����(kl222@126.com)

---------------------------------------

### ����

- �� cmake , ����ʹ�ô˷�������

      git clone https://github.com/KangLin/ChineseChessControl.git
      mkdir build
      cd build
      cmake ..
      cmake --build .

### ����
#### VC6.0

- �� ActiveX control test container ����  
![�� ActiveX control test container ����](Image/OpenActivexControlTestContainer.png)
- ע���й�����ؼ�  
  ��һ���ڱ����װʱ�����Զ���ɡ����û�гɹ������԰����淽��֮һע�᣺  
  **ע��**:��Ҫ����ԱȨ��
  + �ֹ�ע�ᣬʹ�� regsvr32 ����

        regsvr32 /s /c "D:\Source\ChineseChessControl\Src\.\DebugU\ChineseChessControl.ocx" 

  + �� ActiveX control test container ע��
    - ��ע��ؼ�  
![��ע��ؼ�](Image/OpenRegisterControl.png)
    - ע���й�����ؼ�  
      + ![](Image/RegisterControl.PNG)
      + ![](Image/RegisterChineseChessControl.PNG)
      + ![](Image/RegisteredChineseChessControl.PNG)
- �����й�����ؼ�  
![](Image/InsertChineseChessControl.PNG)
- ����  
![](Image/Debug.PNG)

#### VS 2017

- �� VS 2010 û���Դ� ActivX control test container ���ߣ����������ӳ���ķ�ʽ�ṩ����������Դ� vc6.0 �и��ƹ��������ߣ��� VS 2017 ��װ�����ӳ����б���õ���

[Testing Properties and Events with Test Container](https://docs.microsoft.com/en-us/cpp/mfc/testing-properties-and-events-with-test-container)

���û��װ����ɴ� github ������[Դ��](https://github.com/microsoft/VCSamples/tree/master/VC2010Samples/MFC/ole/TstCon)

- ����->�ⲿ����->���
  + ![](Image/OpenActivexControlTestContainerVC2013.png)
  + ![](Image/AddActivexControlTestContainer.PNG)
- ʣ�µĵ��Բ���������VC6.0��һ��

### ʹ��

- [��Σ��� Windows ������� ActiveX �ؼ�](https://docs.microsoft.com/zh-cn/dotnet/framework/winforms/controls/how-to-add-activex-controls-to-windows-forms)

### �ؼ�

[�ӿ��ļ�](../Src/ActiveX/ChineseChessActiveX.idl)

#### ����:

- Enabled: ������ֹ�ؼ�
- QiPangColor: ������ɫ
- TiShiBoxColor: ��ʾ�����ɫ
- QiPangPicture: ����ͼƬ
- BoardLayout: ���̲��֡�ȡ����ֵ��
  + NoQi = 0,
  + OnlyTopBlack = 1,
  + OnlyBottomRed = 2,
  + SwapRedBetweenBlack = 4,
  + OnlyTopRed = OnlyTopBlack | SwapRedBetweenBlack,
  + OnlyBottomBlack = OnlyBottomRed | SwapRedBetweenBlack,
  + TopBlackAndBottomRed = OnlyTopBlack | OnlyBottomRed,
  + TopRedAndBottomBlack = TopBlackAndBottomRed | SwapRedBetweenBlack  
  **ע��**��������ֲ���ȫ�������û��������ԣ�Enabled���Ծ����Ƿ����塣
- EnablePromptSound: ������ʾ��
- EnablePromptMessage: ������ʾ��Ϣ

#### ����:

- NextStep(): ��һ��
- PreviouStep(): ��һ��
- GoChess(SHORT i, SHORT j): ����
- SaveChessGame(BSTR szFile): �������
- LoadChessGame(BSTR szFile): װ����ֲ�����Ϊ��ʼ״̬

#### �¼�:

- EventGoChess(short x, short y, ENUM_QiZi chess):���塣

### ����
#### �ַ�����

WIndows ����ϵͳ�ַ�����Ĭ��ΪGB2313��
linuxϵͳ���ַ�����һ��ʹ�� UTF-8 ��
���Ա���Ŀ��ƽ̨���ֵ��ļ��е��ַ����**���ֽڱ���**��
����VC��صĲ����ļ�ʹ�� UNICODE ���루λ�ڣ�Src\ActiveX �� App\MFC����
