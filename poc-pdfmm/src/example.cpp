/**
 * Copyright (C) 2006 by Dominik Seichter <domseichter@web.de>
 *
 * Licensed under GNU General Public License 2.0 or later.
 * Some rights reserved. See COPYING, AUTHORS.
 */

// src: https://github.com/pdfmm/pdfmm/blob/v0.9.22/examples/helloworld/helloworld.cpp

// Include the standard headers for cout to write
// some output to the console.
#include <iostream>

// Now include all pdfmm header files, to have access
// to all functions of pdfmm and so that you do not have
// to care about the order of includes.
//
// You should always use pdfmm.h and not try to include
// the required headers on your own.
#include <pdfmm/pdfmm.h>

// All pdfmm classes are member of the pdfmm namespace.
using namespace std;
using namespace mm;

void PrintHelp()
{
    std::cout << "This is a example application for the pdfmm PDF library." << std::endl
        << "It creates a small PDF file containing the text >Hello World!<" << std::endl
        << "Please see https://github.com/pdfmm/pdfmm for more information" << std::endl << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "  examplehelloworld [outputfile.pdf]" << std::endl << std::endl;
}

void HelloWorld(const string_view& filename)
{
    // The document is written directly to filename while being created.
    PdfMemDocument document;

    // PdfPainter is the class which is able to draw text and graphics
    // directly on a PdfPage object.
    PdfPainter painter;

    // This pointer will hold the page object later.
    // PdfSimpleWriter can write several PdfPage's to a PDF file.
    PdfPage* page;

    // A PdfFont object is required to draw text on a PdfPage using a PdfPainter.
    // pdfmm will find the font using fontconfig on your system and embedd truetype
    // fonts automatically in the PDF file.
    PdfFont* font;

    try
    {
        // The PdfDocument object can be used to create new PdfPage objects.
        // The PdfPage object is owned by the PdfDocument will also be deleted automatically
        // by the PdfDocument object.
        //
        // You have to pass only one argument, i.e. the page size of the page to create.
        // There are predefined enums for some common page sizes.
        page = document.GetPages().CreatePage(PdfPage::CreateStandardPageSize(PdfPageSize::A4));

        // Set the page as drawing target for the PdfPainter.
        // Before the painter can draw, a page has to be set first.
        painter.SetCanvas(page);

        // Create a PdfFont object using the font "Arial".
        // The font is found on the system using fontconfig and embedded into the
        // PDF file. If Arial is not available, a default font will be used.
        //
        // The created PdfFont will be deleted by the PdfDocument.
        font = document.GetFontManager().GetFont("Arial");

        // If the PdfFont object cannot be allocated return an error.
        if (font == nullptr)
            PDFMM_RAISE_ERROR(PdfErrorCode::InvalidHandle);

        // Set the font as default font for drawing.
        // A font has to be set before you can draw text on
        // a PdfPainter.
        painter.GetTextState().SetFont(font, 18);

        // You could set a different color than black to draw
        // the text.
        //
        // painter.SetColor(1.0, 0.0, 0.0);

        // Actually draw the line "Hello World!" on to the PdfPage at
        // the position 2cm,2cm from the top left corner.
        // Please remember that PDF files have their origin at the
        // bottom left corner. Therefore we substract the y coordinate
        // from the page height.
        //
        // The position specifies the start of the baseline of the text.
        //
        // All coordinates in pdfmm are in PDF units.
        painter.DrawText("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЬЫЭЮЯ", 56.69, page->GetRect().GetHeight() - 56.69);

        // Tell pdfmm that the page has been drawn completely.
        // This required to optimize drawing operations inside in pdfmm
        // and has to be done whenever you are done with drawing a page.
        painter.FinishDrawing();

        // Set some additional information on the PDF file.
        document.GetInfo().SetCreator(PdfString("examplahelloworld - A pdfmm test application"));
        document.GetInfo().SetAuthor(PdfString("Dominik Seichter"));
        document.GetInfo().SetTitle(PdfString("Hello World"));
        document.GetInfo().SetSubject(PdfString("Testing the pdfmm PDF Library"));
        document.GetInfo().SetKeywords(PdfString("Test;PDF;Hello World;"));

        // The last step is to close the document.
        document.Save(filename);
    }
    catch (PdfError& e)
    {
        // All pdfmm methods may throw exceptions
        // make sure that painter.FinishPage() is called
        // or who will get an assert in its destructor
        try
        {
            painter.FinishDrawing();
        }
        catch (...)
        {
            // Ignore errors this time
        }

        throw e;
    }
}

int main(int argc, char* argv[])
{
    // Check if a filename was passed as commandline argument.
    // If more than 1 argument or no argument is passed,
    // a help message is displayed and the example application
    // will quit.
    if (argc != 2)
    {
        PrintHelp();
        return -1;
    }

    // All pdfmm functions will throw an exception in case of an error.
    //
    // You should catch the exception to either fix it or report
    // back to the user.
    //
    // All exceptions pdfmm throws are objects of the class PdfError.
    // Thats why we simply catch PdfError objects.
    try
    {
        // Call the drawing routing which will create a PDF file
        // with the filename of the output file as argument.
        HelloWorld(argv[1]);
    }
    catch (PdfError& err)
    {
        // We have to check if an error has occurred.
        // If yes, we return and print an error message
        // to the commandline.
        err.PrintErrorMsg();
        return (int)err.GetError();
    }

    // The PDF was created sucessfully.
    std::cout << std::endl
        << "Created a PDF file containing the line \"Hello World!\": " << argv[1] << std::endl << std::endl;

    return 0;
}
