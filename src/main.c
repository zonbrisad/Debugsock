/**
 *---------------------------------------------------------------------------
 * @brief    Library for debugprint via a domainsocket
 *
 * @file     main.c
 * @author   Peter Malmberg <peter.malmberg@gmail.com>
 * @date     2018-03-04
 * @license  MIT
 *
 *---------------------------------------------------------------------------
 *
 *
 */


// Includes -----------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <glib-2.0/glib.h>
#include <signal.h>

#include "main.h"
#include "debugsock.h"

// Macros -------------------------------------------------------------------


// Prototypes ---------------------------------------------------------------


gboolean opt_callback(const gchar *option_name, const gchar *value, gpointer data, GError **error);
void sigint(int sig);
void sighup(int sig);
void sigusr1(int sig);
void sigusr2(int sig);
void sigterm(int sig);

// Variables ----------------------------------------------------------------

GMainLoop *mLoop;
static gboolean opt_verbose;

static gint      opt_integer = 42;
static gdouble   opt_double  = 42.42;
static gchar    *opt_string  = "Kalle";
static gchar    *opt_file    = "F";
static gboolean  opt_bool    = FALSE;

static gboolean  opt_dserver = FALSE;
static gboolean  opt_dclient = FALSE;

static gboolean  opt_verbose = FALSE;
static gboolean  opt_version = FALSE;

static GOptionEntry entries[] = {
	{ "dserver",  'd', 0, G_OPTION_ARG_NONE,     &opt_dserver, "Debug server",  NULL },
	{ "dclient",  'c', 0, G_OPTION_ARG_NONE,     &opt_dclient,  "Debug client",  NULL },
	
//  { "integer",  'i', 0, G_OPTION_ARG_INT,      &opt_integer,  "Integer option",  "nr" },
//  { "string",   's', 0, G_OPTION_ARG_STRING,   &opt_string,   "String option",   "nr" },
//  { "double",   'd', 0, G_OPTION_ARG_DOUBLE,   &opt_double,   "Double option",   "d"  },
//  { "file",     'f', 0, G_OPTION_ARG_FILENAME, &opt_file,     "File option",     NULL },
//  { "callback", 'c', 0, G_OPTION_ARG_CALLBACK, opt_callback,  "Callback option", NULL },
  
  { "verbose",  'v', 0, G_OPTION_ARG_NONE,     &opt_verbose,  "Verbose output",  NULL },
  { "version",   0,  0, G_OPTION_ARG_NONE,     &opt_version,  "Version info",    NULL },
  { NULL }
};                                                                                                                                      


// Code ---------------------------------------------------------------------


gboolean opt_callback(const gchar *option_name, const gchar *value, gpointer data, GError **error) {
  printf("Callback function for option %s,  value=%s\n", option_name, value);
  return 1;
}
void sigint(int sig) {
  exit(0);
}

void sighup(int sig) {

}

void sigusr1(int sig) {

}

void sigusr2(int sig) {

}

void sigterm(int sig) {

}

#define DEBUGSOCK "DEBUGSOCK.sock"

int main(int argc, char *argv[]) {

  GError *error = NULL;
  GOptionContext *context;
  signal(SIGINT, sigint);
  signal(SIGHUP, sighup);
  signal(SIGUSR1, sigusr1);
  signal(SIGUSR2, sigusr2);
  signal(SIGTERM, sigterm);

  context = g_option_context_new ("- what the program does");
  g_option_context_add_main_entries (context, entries, NULL);
  
  g_option_context_set_summary(context, "My summary text...");
  g_option_context_set_description(context, "My description text");
  
  if (!g_option_context_parse (context, &argc, &argv, &error)) {
    g_print ("option parsing failed: %s\n", error->message);
    exit (1);
  }
	
	if (opt_dserver) {
		xdomainServer(DEBUGSOCK);
	}
	
	if (opt_dclient) {
		xdomainClient(DEBUGSOCK);
	}
                  
  if (opt_version) {
    printf("Application version %s\n", APP_VERSION);
    exit(0);
  }
}
