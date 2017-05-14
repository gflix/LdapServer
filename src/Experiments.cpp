#include <signal.h>
#include <unistd.h>
#include <Config.h>
#include <common/Log.h>

#include <asn-one-objects/IntegerAsnOneObject.h>
#include <asn-one-objects/OctetStringAsnOneObject.h>
#include <asn-one-objects/SequenceAsnOneObject.h>

using namespace std;

int main(int argc, char* argv[])
{
    Flix::IntegerAsnOneObject* tempI = new Flix::IntegerAsnOneObject();
    Flix::OctetStringAsnOneObject* tempO = new Flix::OctetStringAsnOneObject();
    Flix::SequenceAsnOneObject* tempS = new Flix::SequenceAsnOneObject();

    Flix::StreamBuffer tempBuffer;

    LOG_DEBUG("-- Integer --");
    tempBuffer = tempI->serialize();
    tempBuffer.dump();
    tempI->setValue(3);
    tempBuffer = tempI->serialize();
    tempBuffer.dump();
    tempI->setValue(255);
    tempBuffer = tempI->serialize();
    tempBuffer.dump();
    tempI->setValue(256);
    tempBuffer = tempI->serialize();
    tempBuffer.dump();
    tempI->setValue(65530);
    tempBuffer = tempI->serialize();
    tempBuffer.dump();
    tempI->setValue(16777215);
    tempBuffer = tempI->serialize();
    tempBuffer.dump();
    tempI->setValue(2147483647);
    tempBuffer = tempI->serialize();
    tempBuffer.dump();

    LOG_DEBUG("-- Octet string --");
    tempBuffer = tempO->serialize();
    tempBuffer.dump();
    tempO->setValue("Dies ist ein möglicherweise sehr langer und sehr ermüdender Text, aber das soll so sein, weil wir wollen ja ausprobieren, wie sich das ganze mit langen Texten verträgt. Und überhaupt, wer sagt denn eigentlich, dass hier schon Ende sein soll? Gleich wird es hageln vor Fehlern, wo man sich lange fragen muss woher die Fehler denn kommen sollen.");
    tempBuffer = tempO->serialize();
    tempBuffer.dump();
    tempO->setValue("ABCD");
    tempBuffer = tempO->serialize();
    tempBuffer.dump();

    LOG_DEBUG("-- Sequence --");
    tempBuffer = tempS->serialize();
    tempBuffer.dump();
    tempS->appendSubObject(tempI);
    tempBuffer = tempS->serialize();
    tempBuffer.dump();
    tempS->appendSubObject(tempO);
    tempBuffer = tempS->serialize();
    tempBuffer.dump();

    delete tempS;

    delete Flix::Log::getInstance();

    return 0;
}
