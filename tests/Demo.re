open Respect.Dsl;

open Respect.Runner;

open Respect.Matcher;

open TestHelpers;

let exec x => ExampleGroup.empty |> applyOperation x |> run;

exception TestFailed string;

let beFailure result =>
  switch result {
  | Respect.Runner.TestSucceeded => Respect.Matcher.Failure
  | Respect.Runner.TestFailed => Success ()
  };

describe
  "TestContext"
  [
    describe
      "Adding data to context"
      [
        it
          "Makes the data retrievable"
          (
            fun _ => {
              let x = TestContext.create ();
              x |> TestContext.add "x" 42;
              x |> TestContext.get "x" |> should (equal 42)
            }
          )
      ]
  ] |> register;

describe
  "Runner"
  [
    describe
      "example throws an exception"
      [
        it
          "returns an error message"
          (
            fun _ => {
              let result =
                anExampleGroup |> withExampleCode (fun _ => raise (TestFailed "")) |> run;
              result |> should beFailure
            }
          )
      ] /*it "returns an error message" (fun _ => {*/,
    /*anExampleGroup |> withExampleCode (fun _ => append "x") |> run;*/
    /*});*/
    it
      "executes the example code"
      (
        fun _ => {
          let lines = ref [];
          let append line => lines := [line, ...!lines];
          anExampleGroup |> withExampleCode (fun _ => append "x") |> run |> ignore;
          !lines |> should (equal ["x"])
        }
      )
  ] |> register;
