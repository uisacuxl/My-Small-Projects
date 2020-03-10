// It's probably useless but I learned htk using this.

#include<gtk/gtk.h>
#include<stdio.h>
#include<string.h>

static gboolean doStuffOnClose() {
	return FALSE;
}

FILE *dictionary;
GtkWidget *outputContainer, *entryToCopy, *inputEntry, *mainContainer;

static void rowSelected() {
	gtk_entry_set_text(GTK_ENTRY(entryToCopy),
			gtk_label_get_text(
					GTK_LABEL(
							gtk_bin_get_child(
									GTK_BIN(
											gtk_list_box_get_selected_row(
													GTK_LIST_BOX(
															outputContainer)))))));
}

static void clickedFindButton() {
// Destroy container
	static int firstTimeClickingFind = 1;
	if (firstTimeClickingFind)
		firstTimeClickingFind = 0;
	else
		gtk_container_remove(GTK_CONTAINER(mainContainer), outputContainer);

// Replace container
	outputContainer = gtk_list_box_new();
	g_signal_connect(outputContainer, "row-selected", G_CALLBACK(rowSelected),
			NULL);
	gtk_list_box_set_selection_mode(GTK_LIST_BOX(outputContainer),
			GTK_SELECTION_SINGLE);

	gtk_container_add(GTK_CONTAINER(mainContainer), outputContainer);

	gtk_widget_show(outputContainer);

// Actual program {
	const char *allowed_old = gtk_entry_get_text(GTK_ENTRY(inputEntry));
	int allowedLettersLen = strlen(allowed_old);
	char allowed[allowedLettersLen];
	strcpy(allowed, allowed_old);

	// Make lowercase.
	for (int i = 0; i < allowedLettersLen; i++) {
		if (allowed[i] > '@' && allowed[i] < '[') {
			allowed[i] += ' ';
		}
	}

	char word[64];
	while (fgets(word, 64, dictionary) != NULL) {
		word[strlen(word) - 1] = '\000';
		int LetterNotValid;
		/* loop through all the letters of word
		 */for (int i = 0, l = strlen(word); i < l; i++) {
			LetterNotValid = 1;
			//loop through all allowed letters
			for (int j = 0; j < allowedLettersLen; j++)
				//check if word[i] is an allowed letter
				if (word[i] == allowed[j]) {
					LetterNotValid = 0;
					break;
				}
			if (LetterNotValid)
				goto endOfLoop;
		}
		GtkWidget *label = gtk_label_new(word);
		gtk_widget_set_can_focus(label, FALSE);
		gtk_container_add(GTK_CONTAINER(outputContainer), label);
		gtk_widget_show(label);
		endOfLoop: /*/*/;
	}
// } It's funny that the actual program is only like 30 lines.
	rewind(dictionary);
}

int main() {

	gtk_init(NULL, NULL);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (window,"Find words");

// Add file chooser dialogue {

	GtkWidget *dialog = gtk_file_chooser_dialog_new("Select a dictionary file",
			GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel",
			GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);

	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		dictionary = fopen(filename, "r");
		g_free(filename);
	} else {
		gtk_main_quit();
	}

	gtk_widget_destroy(dialog);

// }

//Make window close when clicked close button.
	g_signal_connect(window, "delete-event", G_CALLBACK(doStuffOnClose), NULL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	//The container that holds the first five elements
	GtkWidget *inputContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *label1 = gtk_label_new(
			"Enter the letters to find words that only contain those letters.");
	gtk_container_add(GTK_CONTAINER(inputContainer), label1);

	// The gtk entry where the word is entered
	inputEntry = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(inputContainer), inputEntry);

	//The button called find
	GtkWidget *findButton = gtk_button_new_with_label("Find");
	g_signal_connect(findButton, "clicked", G_CALLBACK(clickedFindButton),
			NULL);
	gtk_container_add(GTK_CONTAINER(inputContainer), findButton);

	GtkWidget *label2 =
			gtk_label_new(
					"If you select a word, it will be displayed below so it's easy to copy.");
	gtk_container_add(GTK_CONTAINER(inputContainer), label2);

	// The gtk entry where the selected word is displayed
	entryToCopy = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(inputContainer), entryToCopy);

	// The container that holds the inputContainer and the
	mainContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(mainContainer), inputContainer);

	GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
			GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(scroll), mainContainer);
	gtk_container_add(GTK_CONTAINER(window), scroll);
	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
