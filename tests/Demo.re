open Respect.Dsl;
open Respect.Runner;
open Respect.Domain;
open Respect.Matcher;

let exec x => ExampleGroup.empty |> applyOperation x |> run;

let beFailure result =>
  switch result {
  | Respect.Domain.TestSucceeded => MatchFailure (Obj.repr ())
  | Respect.Domain.TestFailed => MatchSuccess ()
  };

describe "TestContext" [
  describe "Adding data to context" [
    it_w "Makes the data retrievable" (
      fun _ => {
        let ctx = TestContext.create ();
        ctx |> TestContext.add "key" 42;
        ctx |> TestContext.get "key" |> shoulda (equal 42)
        }
    )
  ]
] |> register;

describe "Async tests" [
  it_a "has an async test" (
    fun _ cb => {
      let work () => cb TestSucceeded;
      Js.Global.setTimeout work 10 |> ignore
      }
  ),

  it_w "Implements async match" (fun _ =>{
    let asyncMatcher () => AsyncMatchResult (fun cb => {
      Js.Global.setTimeout (fun () => cb (MatchSuccess ())) 10 |> ignore;
    });
    () |> shoulda asyncMatcher;
  })
] |> register;
