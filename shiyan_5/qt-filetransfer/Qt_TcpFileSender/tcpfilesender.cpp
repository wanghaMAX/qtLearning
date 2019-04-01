#include "tcpfilesender.h"

TcpFileSender::TcpFileSender(QWidget *parent) : QDialog(parent)
{
    loadSize = 4*1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
    clientProgressBar = new QProgressBar;
    clientStatusLabel = new QLabel(QStringLiteral("客戶端就緒"));
    startButton = new QPushButton(QStringLiteral("開始"));
    openButton = new QPushButton(QStringLiteral("開檔"));
    quitButton = new QPushButton(QStringLiteral("退出"));
    lineEdit1 = new QLineEdit(this);
    label1 = new QLabel(this);
    label2 = new QLabel(this);
    spinbox = new QSpinBox(this);
    label1->setText("Server IP:");
    label2->setText("Server Port:");
    spinbox->setMaximum(65535);
    startButton->setEnabled(false);
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(startButton,QDialogButtonBox::ActionRole);
    buttonBox->addButton(openButton,QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton,QDialogButtonBox::RejectRole);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(clientProgressBar);
    mainLayout->addWidget(clientStatusLabel);
    mainLayout->addWidget(label1);
    mainLayout->addWidget(lineEdit1);
    mainLayout->addWidget(label2);
    mainLayout->addWidget(spinbox);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(QStringLiteral("檔案傳送客戶端 40543229"));
    connect(startButton,SIGNAL(clicked()),this,SLOT(start()));
    connect(openButton,SIGNAL(clicked()),this,SLOT(openFile()));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(&tcpClient,SIGNAL(connected()),this,SLOT(startTransfer()));
    connect(&tcpClient,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
}

TcpFileSender::~TcpFileSender(){}

QString ip;

void TcpFileSender::start(){
    ip = lineEdit1->text();
    startButton->setEnabled(false);
    bytesWritten = 0;
    clientStatusLabel->setText(QStringLiteral("系統連線中......"));
    tcpClient.connectToHost(QHostAddress(ip),spinbox->value());
}

void TcpFileSender::startTransfer(){
    localFile = new QFile(fileName);
    if(!localFile->open(QFile::ReadOnly)){
        QMessageBox::warning(this,QStringLiteral("應用程式"),QStringLiteral("無法讀取 %1\n%2.").arg(fileName).arg(localFile->errorString()));
        return;
    }
    totalBytes = localFile->size();
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_6); //設定資料格式版本號
    QString currentFile = fileName.right(fileName.size()-fileName.lastIndexOf("/")-1);
    sendOut<<qint64(0)<<qint64(0)<<currentFile;
    totalBytes += outBlock.size();
    sendOut.device()->seek(0); //輸出指標移到頭端
    sendOut<<totalBytes<<qint64((outBlock.size()-sizeof(qint64)*2));
    bytesToWrite = totalBytes - tcpClient.write(outBlock);
    clientStatusLabel->setText(QStringLiteral("已連線"));
    outBlock.resize(0);//清空outBlock

}

void TcpFileSender::updateClientProgress(qint64 a){
   bytesWritten += (int) a;
   if(bytesToWrite>0){
       outBlock = localFile->read(qMin(bytesToWrite,loadSize));
       bytesToWrite -= (int) tcpClient.write(outBlock);
       outBlock.resize(0);
   }
   else{
       localFile->close();
   }
   clientProgressBar->setMaximum(totalBytes);
   clientProgressBar->setValue(bytesWritten);
   clientStatusLabel->setText(QStringLiteral("已傳送 %1 bytes").arg(bytesWritten));
}

void TcpFileSender::openFile(){
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty()) startButton->setEnabled(true);
}
